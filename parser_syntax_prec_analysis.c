#include "parser_syntax_prec_analysis.h"
#include "scanner.h"
#include "parser.h"

int parser_parse_expression(){
    sToken *token;
    do{
        token = getNextToken();
    } while(!(cmp_token(token, T_KEYWORD, "then") || cmp_token(token, T_KEYWORD, "do") || cmp_token_type(token, T_EOL)));
    store_token(token);
    return 0;
}
