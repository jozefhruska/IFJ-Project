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
#include "token.h"
#include "scanner.h"
#include "parser.h"

#define FILE_ERROR 5

int main1(int argc, char** argv)
{
    
    sToken *token;

    FILE *f;
    f=fopen(argv[1], "r");

    setSourceFile(f);

    do
    {
        token = getNextToken();
        // printf("%d\n", state);
        if (token->type == -1 || token->type == 0 || token->type == 1) {
            printf("ending state: %d\n", token->type);
            break;
        }
        else if (token->type == T_INT) 
        {
            printf("====\ntoken value: %ld\nstate: %d\n", (long)token->data, token->type);
        }
        else if (token->type == T_DOUBLE) 
        {
            printf("====\ntoken value: %f\nstate: %d\n", *((double *)(token->data)), token->type);
        }
        else 
        {
            printf("====\ntoken value: %s\nstate: %d\n", (char *)token->data, token->type);
        }
    } while (1);
    
    return 0;
}