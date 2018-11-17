#include "parser_syntax_prec_analysis.h"
#include "scanner.h"
#include "parser.h"

int parser_parse_expression(){
    sToken *token;
    do{
        token = getNextToken();
    } while(!(cmp_token(token, T_KEYWORD, "then") || cmp_token(token, T_DELIMITER, ")")));
    if(cmp_token(token, T_DELIMITER, ")")) store_token(token);
    return 0;
}
