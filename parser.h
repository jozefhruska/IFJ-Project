#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#define PARSE_SUCCESS 1


int parse();
int cmp_token(sToken*, Ttoken, char*);

#endif
