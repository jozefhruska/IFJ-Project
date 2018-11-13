#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "_pseudoScanner.h"
#include "parser_syntax_rules.h"
#include "error_handler.h"

int parse(){
    int result = parser_parse_prog();
    return result;
}
