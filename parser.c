#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "parser_syntax_rules.h"
#include "parser_syntax_prec_analysis.h"
#include "error_handler.h"
#include "generator.h"
#include "semantic.h"

int parse(FILE *source){

	setSourceFile(source);
	
    _Init();
	int result = parser_parse_prog();

	if (false == eachFunctionDefined()) {
	    error_fatal(ERROR_SEMANTIC_DEF);
	}

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
        if(current->type == _NONTERMINAL){
            printf("E (TYPE = %d, PREC_TAB_ID = %d, LEX_TOKEN_TYPE = %d)\n", current->token_attr, current->type, current->token_type, current->lex_token_type);
        } else {
            printf("%s (TYPE = %d, PREC_TAB_ID = %d, LEX_TOKEN_TYPE = %d)\n", (char*)current->token_attr, current->type, current->token_type, current->lex_token_type);
        }
        current = current->next;
    }
    printf("===== BOT STACK =====\n");
}
