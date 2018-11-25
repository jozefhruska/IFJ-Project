#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "parser_syntax_rules.h"
#include "error_handler.h"

int parse(FILE *source){

	setSourceFile(source);
	
	int result = parser_parse_prog();
    return result;
}

int cmp_token_type(sToken* token, Ttoken token_type){
    return( token->type == token_type );
}

int cmp_token(sToken* token, Ttoken token_type, char *token_data){
	return( token->type == token_type && strcmp(token->data, token_data) == 0 );
}

void debug_print_token(sToken *token){
    printf("Token: %s (type = %d)\n", (char*)token->data, token->type);
}

void debug_print_PAStack(sPA_Stack *stack){
    if(stack->firstItem == NULL) return;
    sPA_Stack_Item *current = stack->firstItem;
    printf("===== TOP STACK =====\n");
    while(current != NULL){
        printf("%s (TYPE = %d, TOKEN_ID = %d)\n", current->token_attr, current->type, current->token_type);
        current = current->next;
    }
    printf("===== BOT STACK =====\n");
}
