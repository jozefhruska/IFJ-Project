#ifndef PARSER_H
#define PARSER_H
#define PARSE_SUCCESS 1
#include "scanner.h"
#include "parser_syntax_prec_analysis.h"



int parse();
int cmp_token_type(sToken*, Ttoken);
int cmp_token(sToken*, Ttoken, char*);

void debug_print_token(sToken*);
void debug_print_PAStack(sPA_Stack*);

#endif
