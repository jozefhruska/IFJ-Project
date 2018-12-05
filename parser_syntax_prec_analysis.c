#include "parser_syntax_prec_analysis.h"
#include "scanner.h"
#include "parser.h"
#include "error_handler.h"
#include "string.h"
#include "parser_syntax_rules.h"
#include "semantic.h"


char __GLOBAL_PREC_TABLE[7][7] = {
/*            +/-  / *  REL   (    )   ID    $               */
/* +/- */    {'>', '<', '>', '<', '>', '<', '>'},
/* / * */    {'>', '>', '>', '<', '>', '<', '>'},
/* REL */    {'<', '<', 'X', '<', '>', '<', '>'},
/* (   */    {'<', '<', '<', '<', '=', '<', 'X'},
/* )   */    {'>', '>', '>', 'X', '>', 'X', '>'},
/* ID  */    {'>', '>', '>', 'X', '>', 'X', '>'},
/* $   */    {'<', '<', '<', '<', 'X', '<', 'X'}
};

void PAInit(sPA_Stack **stack){
    (*stack) = (sPA_Stack*)malloc(sizeof(sPA_Stack));
    (*stack)->firstItem = NULL;
}


void PAPush(sPA_Stack *stack, int type, int token_type, int lex_token_type, void *token_attr){
    sPA_Stack_Item *newItem = (sPA_Stack_Item*)malloc(sizeof(sPA_Stack_Item));
    if(newItem == NULL) error_fatal(ERROR_INTERNAL);
    newItem->token_type = token_type;
    newItem->token_attr = token_attr;
    newItem->type = type;
    newItem->lex_token_type = lex_token_type;

    if(stack->firstItem == NULL){
        newItem->next = NULL;
        stack->firstItem = newItem;
    } else {
        newItem->next = stack->firstItem;
        stack->firstItem = newItem;
    }
}

void PAInsertBefore(sPA_Stack *stack, sPA_Stack_Item *stack_item, int type, int token_type, int lex_token_type, void *token_attr){
    sPA_Stack_Item *tmp = stack->firstItem;
    if(tmp == NULL) error_fatal(ERROR_INTERNAL);
    else if(tmp == stack_item){
        sPA_Stack_Item *newItem = (sPA_Stack_Item*)malloc(sizeof(sPA_Stack_Item));
        if(newItem == NULL) error_fatal(ERROR_INTERNAL);
        newItem->type = type;
        newItem->token_type = token_type;
        newItem->token_attr = token_attr;
        newItem->next = tmp;
        newItem->lex_token_type = lex_token_type;
        stack->firstItem = newItem;
    } else {
        while(!((tmp->next == stack_item) || (tmp->next == NULL))) tmp = tmp->next;
        PAInsertAfter(tmp, type, token_type, _PREC_NULL, token_attr);
    }
}

void PAInsertAfter(sPA_Stack_Item *stack_item, int type, int token_type, int lex_token_type, void *token_attr){
    sPA_Stack_Item *newItem = (sPA_Stack_Item*)malloc(sizeof(sPA_Stack_Item));
    if(newItem == NULL) error_fatal(ERROR_INTERNAL);
    newItem->type = type;
    newItem->token_type = token_type;
    newItem->token_attr = token_attr;
    newItem->next = stack_item->next;
    newItem->lex_token_type = lex_token_type;
    stack_item->next = newItem;
}

sPA_Stack_Item *PAGetTerminal(sPA_Stack *stack){
    sPA_Stack_Item *res = stack->firstItem;
    while(!((res->type == _TERMINAL) || (res == NULL))) res = res->next;
    if(res == NULL) error_fatal(ERROR_SYNTACTIC); //TODO: What goes here omg?
    return res;
}

sPA_Stack_Item *PAPop(sPA_Stack *stack){
    if(stack->firstItem == NULL) return NULL;
    sPA_Stack_Item *toReturn = stack->firstItem;
    stack->firstItem = stack->firstItem->next;
    return toReturn;
}

int parser_parse_expression(){
    sPA_Stack *stack, *subexpression;
    PAInit(&stack);
    PAPush(stack, _TERMINAL, _PREC_DOLAR, _PREC_NULL, "$");

    sPA_Stack_Item *incomming = ConvertTokenToStackItem(getNextToken());
    sPA_Stack_Item *top;

    do{
        top = PAGetTerminal(stack);

        switch(__GLOBAL_PREC_TABLE[top->token_type][incomming->token_type]){
            case '=':
                PAPush(stack, incomming->type, incomming->token_type, incomming->lex_token_type, incomming->token_attr);
                incomming = ConvertTokenToStackItem(getNextToken());
            break;
            case '<':
                PAInsertBefore(stack, top, _SYM_LOWER, _PREC_NULL, _PREC_NULL, "<");
                PAPush(stack, incomming->type, incomming->token_type, incomming->lex_token_type, incomming->token_attr);
                incomming = ConvertTokenToStackItem(getNextToken());
            break;
            case '>':
                PAInit(&subexpression);
                
                sPA_Stack_Item *item = PAPop(stack);

                while(!((item->type == _SYM_LOWER) || (item == NULL))){
                    PAPush(subexpression, item->type, item->token_type, item->lex_token_type, item->token_attr);
                    item = item->next;
                }
                
                if(item == NULL) error_fatal(ERROR_SYNTACTIC);

                ResolveExpression(subexpression);
                //PAPop(stack);
                sPA_Stack_Item *_s = PAPop(stack);
                while(_s->type != _SYM_LOWER) _s = PAPop(stack);

                PAPush(stack, _NONTERMINAL, _PREC_NULL, _PREC_NULL, NULL);
            break;
            default:
                error_fatal(ERROR_SYNTACTIC);
        }


    } while (!((incomming->token_type == _PREC_DOLAR) && ParsedSuccessfully(stack)));
    return 0;
}

int ResolveExpression(sPA_Stack *inputStack){
    /* Input stack is in reverse order. We need to make sure that terminals and non-terminals are in right order! */
    sPA_Stack *stack;
    PAInit(&stack);

    sPA_Stack_Item *tmp = PAPop(inputStack);
    while(tmp != NULL){
        PAPush(stack, tmp->type, tmp->token_type, tmp->lex_token_type, tmp->token_attr);
        tmp = tmp->next;
    }

    sPA_Stack_Item *current_item = PAPop(stack);

    if(current_item->token_type == _PREC_ID){
        // if in a function, try to find ID in private variables or globals
        if (currentFunctionName != NULL) {
            if (
                current_item->lex_token_type == T_ID
                && isVarDeclared((char *) current_item->token_attr) == false
                && isParamDeclared(currentFunctionName, (char *) current_item->token_attr) == false
            ) {
                error_fatal(ERROR_SEMANTIC_DEF);
                return 0;
            }
        } else {
            // if in global, try to find ID only in global variables
            if (
                current_item->lex_token_type == T_ID
                && isVarDeclared((char *) current_item->token_attr) == false
            ) {
                error_fatal(ERROR_SEMANTIC_DEF);
                return 0;
            }
        }
        current_item = PAPop(stack);
        if(current_item != NULL) error_fatal(ERROR_SYNTACTIC);
    } else if(current_item->token_type == _PREC_L_BRACKET){
        current_item = PAPop(stack);
        if(current_item->type == _NONTERMINAL) error_fatal(ERROR_SYNTACTIC);
        current_item = PAPop(stack);
        if(!(current_item->token_type == _PREC_R_BRACKET)) error_fatal(ERROR_SYNTACTIC);
    } else if(current_item->type == _NONTERMINAL){
        current_item = PAPop(stack);
        if(!(current_item->type == _TERMINAL && current_item->token_type == _PREC_PLUS_MINUS) &&
            !(current_item->type == _TERMINAL && current_item->token_type == _PREC_MULT_SUBS) &&
            !(current_item->type == _TERMINAL && current_item->token_type == _PREC_RELATION)) error_fatal(ERROR_SYNTACTIC);
        current_item = PAPop(stack);
        if(current_item->type != _NONTERMINAL) error_fatal(ERROR_SYNTACTIC);
    } else if(current_item->type == _TERMINAL && current_item->token_type == _PREC_RELATION){
        // Some nonsence in expression. Just to make sure... We will exit the compilator :D
        error_fatal(ERROR_SYNTACTIC);
    }

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
    ret->type = _TERMINAL;
    ret->lex_token_type = token->type;

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
        case T_KEYWORD:
            if(cmp_token(token, T_KEYWORD, "then") ||
               cmp_token(token, T_KEYWORD, "do")){
                ret->token_type = _PREC_DOLAR;
                store_token(token);
            } else {
                error_fatal(ERROR_SYNTACTIC);
            }
        break;
        case T_EOL:
            ret->token_type = _PREC_DOLAR;
            store_token(token);
        break;
        default:
            error_fatal(ERROR_SYNTACTIC);
    }

    return ret;
}

int ParsedSuccessfully(sPA_Stack *stack){
    if(stack->firstItem->type == _NONTERMINAL){
        if(stack->firstItem->next->type == _TERMINAL && stack->firstItem->next->token_type == _PREC_DOLAR) return 1;
    }
    return 0;
}
