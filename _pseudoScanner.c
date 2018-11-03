#include <stdio.h>
#include <string.h>
#include "_pseudoScanner.h"

int _i = 0;

sToken tokens[] = {
    { .name = "def", .id = 0},
    { .name = "funkce", .id = 1},
    { .name = "(", .id = 2},
    { .name = ")", .id = 3},
    { .name = "end", .id = 4}
};

int getNextToken(char *target){
    sToken tmp = tokens[_i++];
    strcpy(target, tmp.name);
    return tmp.id;
}
