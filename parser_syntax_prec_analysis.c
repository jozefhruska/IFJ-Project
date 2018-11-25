#include "parser_syntax_prec_analysis.h"
#include "scanner.h"
#include "parser.h"
#include "error_handler.h"
#include "string.h"


char __GLOBAL_PREC_TABLE[7][7] = {
/*            +/-  / *  REL   (    )   ID    $               */
/* +/- */    {'>', '<', '>', '<', '>', '<', '>'},
/* / * */    {'>', '>', '>', '<', '>', '<', '>'},
/* REL */    {'<', '<', 'X', '<', '>', '<', '>'},
/* (   */    {'<', '<', '<', '<', '=', '>', 'X'},
/* )   */    {'>', '>', '>', 'X', '>', 'X', '>'},
/* ID  */    {'>', '>', '>', 'X', '>', 'X', '>'},
/* $   */    {'<', '<', '<', '<', 'X', '<', 'X'}
};

void PAInit(sPA_Stack **stack){
    (*stack) = (sPA_Stack*)malloc(sizeof(sPA_Stack));
    (*stack)->firstItem = NULL;
}


void PAPush(sPA_Stack *stack, int type, int token_type, void *token_attr){
    sPA_Stack_Item *newItem = (sPA_Stack_Item*)malloc(sizeof(sPA_Stack_Item));
    if(newItem == NULL) error_fatal(ERROR_INTERNAL);
    newItem->token_type = token_type;
    newItem->token_attr = token_attr;
    newItem->type = type;

    if(stack->firstItem == NULL){
        newItem->next = NULL;
        stack->firstItem = newItem;
    } else {
        newItem->next = stack->firstItem;
        stack->firstItem = newItem;
    }
}

void PAInsertBefore(sPA_Stack *stack, sPA_Stack_Item *stack_item, int type, int token_type, void *token_attr){
    sPA_Stack_Item *tmp = stack->firstItem;
    if(tmp == NULL) error_fatal(ERROR_INTERNAL);
    else if(tmp == stack_item){
        sPA_Stack_Item *newItem = (sPA_Stack_Item*)malloc(sizeof(sPA_Stack_Item));
        if(newItem == NULL) error_fatal(ERROR_INTERNAL);
        newItem->type = type;
        newItem->token_type = token_type;
        newItem->token_attr = token_attr;
        newItem->next = tmp;
        stack->firstItem = newItem;
    } else {
        while(!((tmp->next == stack_item) || (tmp->next == NULL))) tmp = tmp->next;
        PAInsertAfter(tmp, type, token_type, token_attr);
    }
}

void PAInsertAfter(sPA_Stack_Item *stack_item, int type, int token_type, void *token_attr){
    sPA_Stack_Item *newItem = (sPA_Stack_Item*)malloc(sizeof(sPA_Stack_Item));
    if(newItem == NULL) error_fatal(ERROR_INTERNAL);
    newItem->type = type;
    newItem->token_type = token_type;
    newItem->token_attr = token_attr;
    newItem->next = stack_item->next;
    stack_item->next = newItem;
}

sPA_Stack_Item *PAGetTerminal(sPA_Stack *stack){
    sPA_Stack_Item *res = stack->firstItem;
    while(!((res->type == _TERMINAL) || (res == NULL))) res = res->next;
    if(res == NULL) error_fatal(ERROR_SYNTACTIC); //TODO: What goes here omg?
    return res;
}

sPA_Stack_Item *PAPop(sPA_Stack *stack){
    sPA_Stack_Item *toReturn = stack->firstItem;
    stack->firstItem = stack->firstItem->next;
    return toReturn;
}

int parser_parse_expression(){
    sPA_Stack *stack;
    PAInit(&stack);
    PAPush(stack, _TERMINAL, _PREC_DOLAR, "$");

    sPA_Stack_Item *incomming = ConvertTokenToStackItem(getNextToken());

    do{
        sPA_Stack_Item *top = PAGetTerminal(stack);

        switch(__GLOBAL_PREC_TABLE[top->token_type][incomming->token_type]){
            case '=':
                PAPush(stack, incomming->type, incomming->token_type, incomming->token_attr);
                incomming = ConvertTokenToStackItem(getNextToken());
            break;
            case '<':
                PAPush(stack, _SYM_LOWER, _PREC_NULL, "<");
                PAPush(stack, incomming->type, incomming->token_type, incomming->token_attr);
                incomming = ConvertTokenToStackItem(getNextToken());
            break;
            case '>':
                debug_print_PAStack(stack);
                return 0;
            break;
            default:
                error_fatal(ERROR_SYNTACTIC);
        }

    } while(!(incomming->token_type == _PREC_DOLAR));
    return 0;
}

int pseudo_parser_parse_expression(){
    sToken *token;
    do{
        token = getNextToken();
    } while(!(cmp_token(token, T_KEYWORD, "then") || cmp_token(token, T_KEYWORD, "do") || cmp_token_type(token, T_EOL)));
    store_token(token);
    return 0;
}

sPA_Stack_Item *ConvertTokenToStackItem(sToken *token){
    sPA_Stack_Item *ret = (sPA_Stack_Item*)malloc(sizeof(sPA_Stack_Item));
    ret->next = NULL;
    ret->token_attr = token->data;

    /* Mapping token type to stack item type */
    switch(token->type){
        case T_OPERATOR:
            if((strcmp((char*)token->data, "+") == 0) || (strcmp((char*)token->data, "-") == 0)) ret->token_type = _PREC_PLUS_MINUS;
            else if((strcmp((char*)token->data, "*") == 0) || (strcmp((char*)token->data, "/") == 0)) ret->token_type = _PREC_MULT_SUBS;
            else ret->token_type = _PREC_RELATION;
        break;
        case T_ID:
        case T_INT:
        case T_DOUBLE:
        case T_STRING:
            ret->token_type = _PREC_ID;
        break;
        case T_RIGHT_BRACKET:
            ret->token_type = _PREC_R_BRACKET;
        break;
        case T_LEFT_BRACKET:
            ret->token_type = _PREC_L_BRACKET;
        break;
        default:
            error_fatal(ERROR_SYNTACTIC);
    }

    return ret;
}
