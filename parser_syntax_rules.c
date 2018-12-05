#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "memory_manager.h"

#include "parser.h"
#include "parser_syntax_rules.h"
#include "parser_syntax_prec_analysis.h"

#include "error_handler.h"
#include "scanner.h"
#include "symtable.h"

#include "semantic.h"
#include "generator.h"


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
        free_token(token);
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
        free_token(token);
        error_fatal(ERROR_SYNTACTIC);
    }

    return 0;
}

int parser_parse_func(){
    /* <func> -> ... */
    sToken *token = getNextToken();
    if(!cmp_token(token, T_KEYWORD, "def")) error_fatal(ERROR_SYNTACTIC);
    free_token(token);
    token = getNextToken();
    if(cmp_token_type(token, T_ID)) { // function name
        addFunction((char *) token->data);
        currentFunctionName = (char *) token->data;
        /* generator */
        _Function_start((char *)token->data);
    }
    else
        error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(!cmp_token_type(token, T_LEFT_BRACKET)) error_fatal(ERROR_SYNTACTIC);

    parametersRemaining = getParamCount(currentFunctionName);
    int defaultParametersCount = parametersRemaining;
    parser_parse_params(true, false);

    if (false == isFunctionParamsUnlimited(currentFunctionName) && defaultParametersCount > 0 && 0 != parametersRemaining) {
        // if parameters count in first call and the definition isn't equal
        error_fatal(ERROR_SEMANTIC_PARAM);
    }

    token = getNextToken();
    if(!cmp_token_type(token, T_RIGHT_BRACKET)) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(!cmp_token_type(token, T_EOL)) error_fatal(ERROR_SYNTACTIC);

    parser_parse_body();

    token = getNextToken();
    if(cmp_token(token, T_KEYWORD, "end")) {
        endFunction();
        currentFunctionName = NULL;
        /* Generator */
        _Function_end(NULL);
    }
    else
        error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(!cmp_token_type(token, T_EOL)) error_fatal(ERROR_SYNTACTIC);

    return 0;
}
////////////////////////////// true /////////// false
int parser_parse_params(bool declaration, bool declared) {
    sToken *token = getNextToken();
    if (cmp_token_type(token, T_ID)) {
        /* <params> -> id <params_next> */

        if (declaration) {
            // if parsing function declaration, save the parameter
            parametersRemaining--;
            addParam((char *) token->data, true);
            /* Generator */
            _Function_param((char *)token->data);

        } else {
            // if in function call
            if (declared) {
                isVariableVisibleOrError(token);
                parametersRemaining--;
            } else {
                parametersRemaining++;
            }
        }

        parser_parse_params_next(declaration, declared);
    } else {
        if (
            declaration == false
            && (
                cmp_token_type(token, T_INT)
                || cmp_token_type(token, T_DOUBLE)
                || cmp_token_type(token, T_STRING)
            )
        ) {
            // literals in function call
            if (declared) {
                parametersRemaining--;
            } else {
                parametersRemaining++;
            }

            return parser_parse_params_next(declaration, declared);
        }
        /* <params> -> e */
        store_token(token);
    }

    return 0;
}

int parser_parse_params_next(bool declaration, bool declared) {
    sToken *token = getNextToken();

    if(cmp_token_type(token, T_COMMA)){
        /* <params_next> -> , id <params_next> */
        token = getNextToken();

        if(cmp_token_type(token, T_ID)) {
            if (declaration) {
                // if parsing function declaration, save the parameter
                parametersRemaining--;
                addParam((char *) token->data, true);

                _Function_param((char *) token->data);

            } else {
                // if in function call
                if (declared) {
                    isVariableVisibleOrError(token);
                    parametersRemaining--;
                } else {
                    parametersRemaining++;
                }
            }
        } else {
            if (
                declaration == false
                && (
                    cmp_token_type(token, T_INT)
                    || cmp_token_type(token, T_DOUBLE)
                    || cmp_token_type(token, T_STRING)
                )
            ) {
                // literals in function call
                if (declared) {
                    parametersRemaining--;
                } else {
                    parametersRemaining++;
                }
                return parser_parse_params_next(declaration, declared);
            }

            error_fatal(ERROR_SYNTACTIC);
        }

        return parser_parse_params_next(declaration, declared);
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
              cmp_token_type(token, T_DOUBLE) ||
              cmp_token_type(token, T_STRING)){
        store_token(token);
        parser_parse_expression();
    } else if(cmp_token_type(token, T_ID)){

        sToken *next_token = getNextToken();

        if(cmp_token(next_token, T_OPERATOR, "=")){
            store_token(token);
            store_token(next_token);
            parser_parse_assign();

            // add new variable to sym table
            if (currentFunctionName == NULL) {
                // in global scope
                if (isVarDeclared((char *) token->data) == false) {
                    addVar((char *) token->data);
                }
            } else {
                // function's local variable
                if (isParamDeclared(currentFunctionName, (char *) token->data) == false) {
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
                parser_parse_func_call(true);
            } else {
                /* 
                    We will compare next token to left bracket, 
                    if result is true, than we will throw SEMANTIC error
                    In this case programmer might me trying to 
                    call undeclared function -> REALLY HARD TO RECOGNIZE
                */
                if(cmp_token_type(next_token, T_LEFT_BRACKET) || cmp_token_type(next_token, T_ID))
                {
                    // tried to call function, that wasn't declared yet
                    // add a function to symtable with defined = false
                    // in the end of the compilation must be check if each function is defined
                    addFuncionDefinedLater((char *) token->data);
                    store_token(token);
                    store_token(next_token);
                    parser_parse_func_call(false);
//                    error_fatal(ERROR_SEMANTIC_DEF_FUN);
                } else {
                    store_token(token);
                    store_token(next_token);
                    parser_parse_expression();
                }
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

    _Condition_if();

    token = getNextToken();
    if(!cmp_token_type(token, T_EOL)) error_fatal(ERROR_SYNTACTIC);

    parser_parse_body();

    _Condition_else();

    parser_parse_cond_else_block();

    token = getNextToken();
    if(!cmp_token(token, T_KEYWORD, "end")) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();

    _Condition_end();

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
        /* This was deleted because IT IS NOT IN BASIC ZADANI */
        error_fatal(ERROR_SYNTACTIC);
        //store_token(token);
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

    _While_start();
    parser_parse_body();
    _While_end();

    token = getNextToken();
    if(!cmp_token(token, T_KEYWORD, "end")) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(!cmp_token_type(token, T_EOL)) error_fatal(ERROR_SYNTACTIC);
    return 0;
}

int parser_parse_assign(){
    sToken *token = getNextToken();
    if(!cmp_token_type(token, T_ID)) error_fatal(ERROR_SYNTACTIC);

    _Expression_assign(token);

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
        parser_parse_func_call(true);
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

int parser_parse_func_call(bool declared){
    sToken *token = getNextToken();
    if(!cmp_token_type(token, T_ID)) error_fatal(ERROR_SYNTACTIC);

    // if called function isn't declared, parametersRemaining will be 0 and will increment for each used param
    parametersRemaining = getParamCount((char *) token->data);
    char *functionTokenData = token->data;

    // if unlimited parameters count - e.g. print function - require at least one parameter
    if (isFunctionParamsUnlimited((char *) token->data)) {
        parametersRemaining = 1; // at least 1 param
    }

    token = getNextToken();
    if(cmp_token_type(token, T_LEFT_BRACKET)){
        /* <func_call> -> id (<params>) */
        parser_parse_params(false, declared);
        token = getNextToken();
        if(!cmp_token_type(token, T_RIGHT_BRACKET)) error_fatal(ERROR_SYNTACTIC);
    } else {
        /* <func_call> -> id <params> */
        store_token(token);
        parser_parse_params(false, declared);
    }

    if (declared) {
        if (parametersRemaining > 0) { // in normal function 0 is ok, in print function there can be negative value
            error_fatal(ERROR_SEMANTIC_PARAM);
            return 0;
        }

        if (parametersRemaining < 0 && false == isFunctionParamsUnlimited((functionTokenData))) {
            // is there was given more parameters
            error_fatal(ERROR_SEMANTIC_PARAM);
            return 0;
        }
    } else {
        // if calling a function that wasn't declared yet, add parameters
        char *currentFunctionNameTmp = currentFunctionName;
        BTNodePtr currentFunctionTmp = currentFunction;
        currentFunctionName = functionTokenData;
        currentFunction = STableSearch(globalSymTable, currentFunctionName);

        for (int i = 0; i < parametersRemaining; i++) {
            char *paramName = malloc(30);
            if (paramName == NULL) {
                error_fatal(ERROR_INTERNAL);
            }

            sprintf(paramName, "param%d", i);

            addParam(paramName, true);
        }

        currentFunctionName = currentFunctionNameTmp;
        currentFunction = currentFunctionTmp;

        parametersRemaining = 0;
    }


    return 0;
}
