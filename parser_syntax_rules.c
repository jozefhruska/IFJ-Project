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
    } else if(cmp_token(token, T_KEYWORD, "if")){ // TODO: Tady příjdou vypsat všechny možnosti, do kterých může <body> zderivovat
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
    /* TODO: DOPLNIT PRAVIDLA PRO LOOP A ASSIGN! */
    if(cmp_token(token, T_KEYWORD, "if")){
        store_token(token);
        parser_parse_cond();
        return parser_parse_body();
    } else {
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
