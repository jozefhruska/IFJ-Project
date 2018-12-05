#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "generator.h"

int main(int argc, char *argv[]){
    printf("Test %s: ", argv[1]);
    fflush(stdout);
    FILE *file = fopen(argv[1], "r");
    int result = parse(file);
    fclose(file);

    if(result == PARSE_SUCCESS){
        printf("\x1b[32mSUCCESSFULLY PARSED\x1b[0m\n");
    } else {
        printf("Error code: %d\n", result);
    }

    resolveAllInstructions();    
    return 0;
}
