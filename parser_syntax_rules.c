#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "parser_syntax_rules.h"
#include "parser_syntax_prec_analysis.h"

#include "error_handler.h"
#include "scanner.h"

int parser_parse_prog(){
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
              cmp_token_type(token, T_ID)){ // TODO: Tady příjdou vypsat všechny možnosti, do kterých může <body> zderivovat
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
    if(!cmp_token_type(token, T_ID)) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(!cmp_token_type(token, T_LEFT_BRACKET)) error_fatal(ERROR_SYNTACTIC);
    parser_parse_params();

    token = getNextToken();
    if(!cmp_token_type(token, T_RIGHT_BRACKET)) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(!cmp_token_type(token, T_EOL)) error_fatal(ERROR_SYNTACTIC);

    parser_parse_body();

    token = getNextToken();
    if(!cmp_token(token, T_KEYWORD, "end")) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(!cmp_token_type(token, T_EOL)) error_fatal(ERROR_SYNTACTIC);

    return 0;
}

int parser_parse_params(){
    sToken *token = getNextToken();
    if(cmp_token_type(token, T_ID)){
        /* <params> -> id <params_next> */
        parser_parse_params_next();
    } else {
        /* <params> -> e */
        store_token(token);
    }

    return 0;
}

int parser_parse_params_next(){
    sToken *token = getNextToken();
    if(cmp_token_type(token, T_COMMA)){
        /* <params_next> -> , id <params_next> */
        token = getNextToken();
        if(!cmp_token_type(token, T_ID)) error_fatal(ERROR_SYNTACTIC);
        return parser_parse_params_next();
    } else {
        /* <params_next> -> e */
        store_token(token);
    }
    return 0;
}

int parser_parse_body(){
    sToken *token = getNextToken();

    if(cmp_token(token, T_KEYWORD, "if")){
        /* <body> -> <cond><body> */
        store_token(token);
        parser_parse_cond();
        return parser_parse_body();
    } else if(cmp_token(token, T_KEYWORD, "while")){
        /* <body> -> <loop><body> */
        store_token(token);
        parser_parse_loop();
        return parser_parse_body();
    } else if(cmp_token_type(token, T_ID)){
        //TODO: Tady se podívat, jestli další token je =
        store_token(token);
        parser_parse_assign();
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
    if(!cmp_token(token, T_OPERATOR, "=")) error_fatal(ERROR_SYNTACTIC);

    /* 
        TODO: Zeptat se sémantiky, jestli je další identifikátor funkce. Pokud ano,
        tak zavolám parsování funcion_call. Pokud ne, tak parsuju expression.
        Pokud se v expression vyskytne nějaká funkce, tak je to error!
    */

    /* <assign> -> id = <func_call> */
    parser_parse_func_call();
    token = getNextToken();
    if(!cmp_token_type(token, T_EOL)) error_fatal(ERROR_SYNTACTIC);
    return 0;
}

int parser_parse_func_call(){
    sToken *token = getNextToken();
    if(!cmp_token_type(token, T_ID)) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(cmp_token_type(token, T_LEFT_BRACKET)){
        /* <func_call> -> id (<params>) */
        parser_parse_params();
        token = getNextToken();
        if(!cmp_token_type(token, T_RIGHT_BRACKET)) error_fatal(ERROR_SYNTACTIC);
    } else {
        /* <func_call> -> id <params> */
        store_token(token);
        parser_parse_params();
    }

    return 0;
}
