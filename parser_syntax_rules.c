#include <stdio.h>
#include "parser_syntax_rules.h"
#include "error_handler.h"
#include "_pseudoScanner.h"
#include "parser.h"

/**
 * Grammar rules for <prog>
 */
int parser_parse_prog(){
    sToken *token = getNextToken();
    switch(token->id){
        /**
         * Rule <prog> => <func><prog>
         */
        case FUNC_DEFINE:
            parser_parse_function();
            parser_parse_prog();
        break;

        /**
         * Rule <prog> => EOF
         */
        case EOF:
            return PARSE_SUCCESS;
        break;
        default:
            error_fatal(ERROR_SYNTACTIC);
    }
}

/**
 * Grammar rules for <func>
 */
int parser_parse_function(){
    sToken *token = getNextToken();
    if(token->id != ID) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(token->id != L_BRACKET) error_fatal(ERROR_SYNTACTIC);

    parser_parse_params();

    token = getNextToken();
    if(token->id != R_BRACKET) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(token->id != EOL) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(token->id != FUNC_END) error_fatal(ERROR_SYNTACTIC);
    return 0;
}

/**
 * Grammar rules for <params>
 */
int parser_parse_params(){
    sToken *token = getNextToken();

    if(token->id == ID){

        /* <params> => id <params_next> */
        parser_parse_params_next();
        return 0;

    } else if(token->id == R_BRACKET){

        /* <params> => ε */
        storeToken(token);
        return 0;

    } else {
        error_fatal(ERROR_SYNTACTIC);
    }

}

/**
 * Grammar rules for <params_next>
 */
int parser_parse_params_next(){
    sToken *token = getNextToken();
    if(token->id == COMMA){

        /* <params_next> => , id <params_next> */
        token = getNextToken();
        if(token->id != ID) error_fatal(ERROR_SYNTACTIC);
        parser_parse_params_next();
        return 0;

    } else if(token->id == R_BRACKET){

        /* <params_next> => ε */
        storeToken(token);

    } else {
        error_fatal(ERROR_SYNTACTIC);
    }
}
