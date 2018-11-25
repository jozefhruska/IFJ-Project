#ifndef __PARSER_PARSE_EXPRESSION
#define __PARSER_PARSE_EXPRESSION
#include "scanner.h"

int _parser_parse_expression();
int parser_parse_expression();

enum __GLOBAL_PREC_TABLE_TYPES {
    _PREC_PLUS_MINUS,
    _PREC_MULT_SUBS,
    _PREC_RELATION,
    _PREC_L_BRACKET,
    _PREC_R_BRACKET,
    _PREC_ID,
    _PREC_DOLAR,
    _PREC_NULL
};

enum __GLOBAL_PREC_STACK_TYPES {
    _NONTERMINAL,
    _TERMINAL,
    _SYM_LOWER,
    _SYM_GREATER
};

typedef struct PREC_ANALYSIS_STACK_ITEM {
    int type;
    int token_type;
    void* token_attr;
    struct PREC_ANALYSIS_STACK_ITEM *next;
} sPA_Stack_Item;

typedef struct PREC_ANALYSIS_STACK {
    sPA_Stack_Item *firstItem;
} sPA_Stack;

void PAInit(sPA_Stack**);
void PAPush(sPA_Stack*, int type, int token_type, void *token_attr);
void PAInsertAfter(sPA_Stack_Item*, int type, int token_type, void *token_attr);
void PAInsertBefore(sPA_Stack*,sPA_Stack_Item*, int type, int token_type, void *token_attr);
sPA_Stack_Item *PAPop(sPA_Stack*);
sPA_Stack_Item *PAGetTerminal(sPA_Stack*);

sPA_Stack_Item *ConvertTokenToStackItem(sToken*);

#endif
