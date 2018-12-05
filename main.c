#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "generator.h"

int main(int argc, char *argv[]){
    //int result = parse(stdin);

		_Condition_if();

		_While_start();
		_While_end();
		
		_Condition_else();
		_Condition_end();

    resolveAllInstructions();
    return 0;
}
