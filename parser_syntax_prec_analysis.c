#include "parser_syntax_prec_analysis.h"
#include "_pseudoScanner.h"

int parser_parse_expression(){
    sToken *token;
    do{
        token = getNextToken();
    } while(!(token->id == THEN_KEYWORD || token->id == R_BRACKET));
    if(token->id != R_BRACKET) storeToken(token);
    return 0;
}