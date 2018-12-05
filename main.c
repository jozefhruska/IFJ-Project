#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "generator.h"

int main(int argc, char *argv[]){
    int result = parse(stdin);
    resolveAllInstructions();
    return 0;
}
