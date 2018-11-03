#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "_pseudoScanner.h"

void parse(){
    char tokenValue[100];
    int retValue = getNextToken(tokenValue);
    printf("Token: %s, ID: %d\n", tokenValue, retValue);
}
