/*
 *	Project: IFJ18
 *	Course: Formal Languages and Compilers
 *	School: Brno University of Technology
 *
 *	Authors:
 *	- Demel Jan <xdemel01@stud.fit.vutbr.cz>
 *	- Sedláček Aleš	<xsedla1c@stud.fit.vutbr.cz>
 *	- Buchta Martin	<xbucht28@stud.fit.vutbr.cz>
 *	- Hruška Jozef <xhrusk25@stud.fit.vutbr.cz>
 *
 *	May the force be with you.
 */

#include <stdio.h>
#include <stdlib.h>

#include "error_handler.h"

void error_fatal(int errorCode) {
	switch (errorCode) {
		case ERROR_LEXICAL:
			fprintf(stderr, "Error: Lexical error!\n");
			break;
		case ERROR_SYNTACTIC:
			fprintf(stderr, "Error: Syntactic error!\n");
			break;
		case ERROR_SEMANTIC_DEF:
			fprintf(stderr, "Error: Semantic error! (Probably undefined or redefined function, variable)\n");
			break;
		case ERROR_SEMANTIC_RUN:
			fprintf(stderr, "Error: Semantic error! (Probably a runtime error caused by usage of incompatibile types)\n");
			break;
		case ERROR_SEMANTIC_PARAM:
			fprintf(stderr, "Error: Semantic error! (Probably caused by wrong number of parameters)\n");
			break;
		case ERROR_SEMANTIC_OTHER:
			fprintf(stderr, "Error: Semantic error!\n");
			break;
		case ERROR_ZERO_DIVISION:
			fprintf(stderr, "Error: Division by zero!\n");
			break;
		case ERROR_INTERNAL:
			fprintf(stderr, "Internal error: Ooops, something went wrong...\n");
			break;
	}
	/* End process with given error code */

    #ifndef ERROR_NOT_EXIT
	    exit(errorCode);
    #endif
}
