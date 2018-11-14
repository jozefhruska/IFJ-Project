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
            printf("EOL successfully reached!\n");
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
    token = getNextToken();
    if(token->id != R_BRACKET) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(token->id != EOL) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(token->id != FUNC_END) error_fatal(ERROR_SYNTACTIC);
    printf("Function successfully parsed!\n");
    return 0;
}
