#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "parser_syntax_rules.h"
#include "parser_syntax_prec_analysis.h"

#include "error_handler.h"
#include "scanner.h"

/**
 * Grammar rules for <prog>
 */
int parser_parse_prog(){
    sToken *token = getNextToken();
    switch(token->type){
        case T_KEYWORD:

            if(cmp_token(token, T_KEYWORD, "def")){
                /**
                 * Rule <prog> => <func><prog>
                 */
                parser_parse_function();
                return parser_parse_prog();

            } else if(cmp_token(token, T_KEYWORD, "if")){
                /**
                 * Rule <prog> => <stat><prog>
                 */
                parser_parse_statement();
                return parser_parse_prog();
            } else {
                error_fatal(ERROR_SYNTACTIC);
            }
        break;

        /**
         * Rule <prog> => EOF
         */
        case T_EOF:
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
    if(token->type != T_ID) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(!cmp_token(token, T_DELIMITER, "(")) error_fatal(ERROR_SYNTACTIC);

    parser_parse_params();

    token = getNextToken();
    if(!cmp_token(token, T_DELIMITER, ")")) error_fatal(ERROR_SYNTACTIC);

    token = getNextToken();
    if(token->type != T_EOL) error_fatal(ERROR_SYNTACTIC);

    /**
     * TODO: Call <commands> RULE! THIS
     * THIS IS BODY OF FUNCTION
    */

    token = getNextToken();
    if(!cmp_token(token, T_KEYWORD, "end")) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(token->type != T_EOL) error_fatal(ERROR_SYNTACTIC);
    return 0;
}

/**
 * Grammar rules for <params>
 */
int parser_parse_params(){
    sToken *token = getNextToken();

    if(token->type == T_ID){

        /* <params> => id <params_next> */
        parser_parse_params_next();
        return 0;

    } else if(cmp_token(token, T_DELIMITER, ")")){

        /* <params> => ε */
        store_token(token);
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
    if(cmp_token(token, T_DELIMITER, ",")){

        /* <params_next> => , id <params_next> */
        token = getNextToken();
        if(token->type != T_ID) error_fatal(ERROR_SYNTACTIC);
        parser_parse_params_next();
        return 0;

    } else if(cmp_token(token, T_DELIMITER, ")")){

        /* <params_next> => ε */
        store_token(token);

    } else {
        error_fatal(ERROR_SYNTACTIC);
    }
}

/**
 * Grammar rules for <stat>
 */
int parser_parse_statement(){
    parser_parse_expression();
    sToken *token = getNextToken();
    if(!cmp_token(token, T_KEYWORD, "then")) error_fatal(ERROR_SYNTACTIC);
    token = getNextToken();
    if(token->type != T_EOL) error_fatal(ERROR_SYNTACTIC);

    parser_parse_commands();
    parser_parse_statement_else_block();
    token = getNextToken();
    if(!cmp_token(token, T_KEYWORD, "end")) error_fatal(ERROR_SYNTACTIC);
    return 0;
}

int parser_parse_statement_else_block(){
    sToken *token = getNextToken();
    if(cmp_token(token, T_KEYWORD, "else")){
        token = getNextToken();
        if(token->type != T_EOL) error_fatal(ERROR_SYNTACTIC);
        parser_parse_commands();
        return 0;
    } else {
        store_token(token);
        return 0;
    }
}

/**
 * Grammar rules for <commands>
 */
int parser_parse_commands(){
    return 0;
}
