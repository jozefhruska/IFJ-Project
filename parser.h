#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#define PARSE_SUCCESS 1


int parse();
int cmp_token_type(sToken*, Ttoken);
int cmp_token(sToken*, Ttoken, char*);

void debug_print_token(sToken*);

#endif
