#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "parser_syntax_rules.h"
#include "error_handler.h"

int parse(FILE *source){
	/*
        int result = parser_parse_prog();
        return result;
    */

	setSourceFile(source);

	/*
    do{
        sToken *myToken = getNextToken();
        if(myToken->type == 1 || myToken->type == 0 || myToken->type == -1) return 0;
	    printf("Token: %d, %s\n", myToken->type, (char*)myToken->data);
    } while(1);
    */
    
	int result = parser_parse_prog();
    return result;
}

int cmp_token(sToken* token, Ttoken token_type, char *token_data){
	return( token->type == token_type && strcmp(token->data, token_data) == 0 );
}
