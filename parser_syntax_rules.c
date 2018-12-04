#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "parser_syntax_rules.h"
#include "parser_syntax_prec_analysis.h"

#include "error_handler.h"
#include "scanner.h"

#include "semantic.h"

int parser_parse_prog(){
    // TODO: init global symbol table once in main, remove untill // TODO: end remove
    static bool globalSymTableInit = false;
    if (globalSymTableInit == false) {
        globalSymTableInit = true;
        initGlobalSymTable();
    }
    // TODO: end remove

    sToken *token = getNextToken();
    if(cmp_token(token, T_KEYWORD, "def")){
        /* <prog> -> <func><prog> */
        store_token(token);
        parser_parse_func();
        return parser_parse_prog();
    } else if(cmp_token_type(token, T_EOF)){
        /* <prog> -> e */
        return PARSE_SUCCESS;
    } else if(cmp_token(token, T_KEYWORD, "if") ||
              cmp_token(token, T_KEYWORD, "while") ||
              cmp_token_type(token, T_ID) ||
              cmp_token_type(token, T_INT) ||
              cmp_token_type(token, T_DOUBLE) ||
              cmp_token_type(token, T_STRING) ||
              cmp_token_type(token, T_EOL)){ // TODO: Tady příjdou vypsat všechny možnosti, do kterých může <body> zderivovat
        /* <prog> -> <body><prog> */
        store_token(token);
        parser_parse_body();
        return parser_parse_prog();
    } else {
        error_fatal(ERROR_SYNTACTIC);
    }

    return 0;
}

int parser_parse_func(){
    /* <func> -> ... */
    sToken *token = getNextToken();
    if(!cmp_token(token, T_KEYWORD, "def")) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(cmp_token_type(token, T_ID)) { // function name
        addFunction((char *) token->data);
        currentFunctoin = (char *) token->data;
    }
    else
        error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(!cmp_token_type(token, T_LEFT_BRACKET)) error_fatal(ERROR_SYNTACTIC);
    parser_parse_params(true);

    token = getNextToken();
    if(!cmp_token_type(token, T_RIGHT_BRACKET)) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(!cmp_token_type(token, T_EOL)) error_fatal(ERROR_SYNTACTIC);

    parser_parse_body();

    token = getNextToken();
    if(cmp_token(token, T_KEYWORD, "end")) {
        endFunction();
        currentFunctoin = NULL;
    }
    else
        error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(!cmp_token_type(token, T_EOL)) error_fatal(ERROR_SYNTACTIC);

    return 0;
}

int parser_parse_params(bool declaration) {
    sToken *token = getNextToken();
    if (cmp_token_type(token, T_ID)) {
        /* <params> -> id <params_next> */

        if (declaration) {
            // if parsing function declaration, save the parameter
            addParam((char *) token->data, true);
        } else {
            // if in function call
            isVariableVisibleOrError(token);
            parametersRemaining--;
        }

        parser_parse_params_next(declaration);
    } else {
        if (
            declaration == false
            && (
                cmp_token_type(token, T_INT)
                || cmp_token_type(token, T_DOUBLE)
                || cmp_token_type(token, T_STRING)
                // TODO: or nil
            )
        ) {
            // literals in function call
            parametersRemaining--;
            return parser_parse_params_next(declaration);
        }
        /* <params> -> e */
        store_token(token);
    }

    return 0;
}

int parser_parse_params_next(bool declaration) {
    sToken *token = getNextToken();

    if(cmp_token_type(token, T_COMMA)){
        /* <params_next> -> , id <params_next> */
        token = getNextToken();

        if(cmp_token_type(token, T_ID)) {
            if (declaration) {
                // if parsing function declaration, save the parameter
                addParam((char *) token->data, true);
            } else {
                // if in function call
                isVariableVisibleOrError(token);
                parametersRemaining--;
            }
        } else {
            if (
                declaration == false
                && (
                    cmp_token_type(token, T_INT)
                    || cmp_token_type(token, T_DOUBLE)
                    || cmp_token_type(token, T_STRING)
                    // TODO: or nil
                )
            ) {
                // literals in function call
                parametersRemaining--;
                return parser_parse_params_next(declaration);
            }

            error_fatal(ERROR_SYNTACTIC);
        }

        return parser_parse_params_next(declaration);
    } else {
        /* <params_next> -> e */
        store_token(token);
    }
    return 0;
}

int parser_parse_body(){
    sToken *token = getNextToken();

    if(cmp_token_type(token, T_EOL)){
        return parser_parse_body();
    } else if(cmp_token(token, T_KEYWORD, "if")){
        /* <body> -> <cond><body> */
        store_token(token);
        parser_parse_cond();
        return parser_parse_body();
    } else if(cmp_token(token, T_KEYWORD, "while")){
        /* <body> -> <loop><body> */
        store_token(token);
        parser_parse_loop();
        return parser_parse_body();
    } else if(cmp_token_type(token, T_INT) ||
              cmp_token_type(token, T_DOUBLE ||
              cmp_token_type(token, T_STRING))){
        store_token(token);
        parser_parse_expression();
    } else if(cmp_token_type(token, T_ID)){

        sToken *next_token = getNextToken();

        if(cmp_token(next_token, T_OPERATOR, "=")){
            store_token(token);
            store_token(next_token);
            parser_parse_assign();

            // add new variable to sym table
            if (currentFunctoin == NULL) {
                // in global scope
                if (isVarDeclared((char *) token->data) == false) {
                    addVar((char *) token->data);
                }
            } else {
                // function's local variable
                if (isParamDeclared(currentFunctoin, (char *) token->data) == false) {
                    addParam((char *) token->data, false);
                }
            }
        } else {
            /*
                TODO: Zeptat se sémantiky, jestli je další identifikátor funkce. Pokud ano,
                tak zavolám parsování funcion_call. Pokud ne, tak parsuju expression.
                Pokud se v expression vyskytne nějaká funkce, tak je to error!
            */

            if (isFunctionDeclared((char *) token->data)) {
                // if the token is function, then call the function
                store_token(token);
                store_token(next_token);
                parser_parse_func_call();
            } else {
                /* 
                    We will compare next token to left bracket, 
                    if result is true, than we will throw SEMANTIC error
                    In this case programmer might me trying to 
                    call undeclared function -> REALLY HARD TO RECOGNIZE
                */
                if(cmp_token_type(next_token, T_LEFT_BRACKET) || cmp_token_type(next_token, T_ID)) error_fatal(ERROR_SEMANTIC_DEF);

                store_token(token);
                store_token(next_token);
                parser_parse_expression();
            }

            token = getNextToken();
            if(!cmp_token_type(token, T_EOL)) error_fatal(ERROR_SYNTACTIC);
        }

        return parser_parse_body();
    } else {
        /* <body> -> e */
        store_token(token);
        return 0;
    }
    return 1;
}

int parser_parse_cond(){
    /* <cond> -> .... */
    sToken *token = getNextToken();
    if(!cmp_token(token, T_KEYWORD, "if")) error_fatal(ERROR_SYNTACTIC);

    parser_parse_expression();

    token = getNextToken();
    if(!cmp_token(token, T_KEYWORD, "then")) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(!cmp_token_type(token, T_EOL)) error_fatal(ERROR_SYNTACTIC);

    parser_parse_body();
    parser_parse_cond_else_block();

    token = getNextToken();
    if(!cmp_token(token, T_KEYWORD, "end")) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(!cmp_token_type(token, T_EOL)) error_fatal(ERROR_SYNTACTIC);
    return 0;
}

int parser_parse_cond_else_block(){
    sToken *token = getNextToken();
    if(cmp_token(token, T_KEYWORD, "else")){
        /* <cond_else_block> -> else EOL
                                <body> */
        token = getNextToken();
        if(!cmp_token_type(token, T_EOL)) error_fatal(ERROR_SYNTACTIC);
        parser_parse_body();
    } else {
        /* <cond_else_block> -> e */
        store_token(token);
    }
    return 0;
}

int parser_parse_loop(){
    /* <loop> -> .... */
    sToken *token = getNextToken();
    if(!cmp_token(token, T_KEYWORD, "while")) error_fatal(ERROR_SYNTACTIC);

    parser_parse_expression();

    token = getNextToken();
    if(!cmp_token(token, T_KEYWORD, "do")) error_fatal(ERROR_SYNTACTIC);

    token = getNextToken();
    if(!cmp_token_type(token, T_EOL)) error_fatal(ERROR_SYNTACTIC);

    parser_parse_body();

    token = getNextToken();
    if(!cmp_token(token, T_KEYWORD, "end")) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(!cmp_token_type(token, T_EOL)) error_fatal(ERROR_SYNTACTIC);
    return 0;
}

int parser_parse_assign(){
    sToken *token = getNextToken();
    if(!cmp_token_type(token, T_ID)) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(cmp_token(token, T_OPERATOR, "=") == false) {
        error_fatal(ERROR_SYNTACTIC);
        return 0; //Fix: Tohle se nikdy nestane
    }

    /*
        TODO: Zeptat se sémantiky, jestli je další identifikátor funkce. Pokud ano,
        tak zavolám parsování funcion_call. Pokud ne, tak parsuju expression.
        Pokud se v expression vyskytne nějaká funkce, tak je to error!
    */

    sToken *upcoming = getNextToken();

    if (cmp_token_type(upcoming, T_ID) && isFunctionDeclared((char *) upcoming->data)) {
        // if the token is function, then call the function
        store_token(upcoming);
        parser_parse_func_call();
    } else {
        store_token(upcoming);
        parser_parse_expression();
    }

    /* <assign> -> id = <func_call> */
    //parser_parse_func_call();
    token = getNextToken();
    if(!cmp_token_type(token, T_EOL)) error_fatal(ERROR_SYNTACTIC);
    return 0;
}

int parser_parse_func_call(){
    sToken *token = getNextToken();
    if(!cmp_token_type(token, T_ID)) error_fatal(ERROR_SYNTACTIC);

    parametersRemaining = getParamCount((char *) token->data);

    token = getNextToken();
    if(cmp_token_type(token, T_LEFT_BRACKET)){
        /* <func_call> -> id (<params>) */
        parser_parse_params(false);
        token = getNextToken();
        if(!cmp_token_type(token, T_RIGHT_BRACKET)) error_fatal(ERROR_SYNTACTIC);
    } else {
        /* <func_call> -> id <params> */
        store_token(token);
        parser_parse_params(false);
    }

    if (parametersRemaining != 0) {
        error_fatal(ERROR_SEMANTIC_PARAM);
        return 0;
    }

    return 0;
}
