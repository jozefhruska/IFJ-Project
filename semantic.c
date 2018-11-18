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
#include <string.h>

#include "semantic.h"
#include "error_handler.h"
#include "symtable.h"
#include "list.h"

STable *globalSymTable; // global symbol table
STable *currentSymTable; // local symbol table for current function

/**
 * @brief Creates new global table
 */
void initGlobalSymTable()
{
    currentSymTable = NULL;

    // init global symbol table
    STableInit(globalSymTable);
}

/**
 * @brief Start of creating new function, or it's declaration
 * @param name
 */
void addFunction(char *name)
{
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return;
    }

    if (currentSymTable == NULL) {
        // current function was not finished!
        // can't define function inside another function
        error_fatal(ERROR_SEMANTIC_OTHER);
        return;
    }

    BTNodePtr symTableItem = STSearch(globalSymTable, name);

    // is the function in the global sym table?
    if (symTableItem != NULL) {
        // the symbol is declared, but is not a function
        if (symTableItem->type != TYPE_FUNCTION) {
            error_fatal(ERROR_SEMANTIC_DEF);
            return;
        }

        // the function is defined yet
        if (symTableItem->defined) {
            error_fatal(ERROR_SEMANTIC_DEF);
            return;
        }
    } else {
        // the function is not in global sym table

        // add function into global table
        // todo create data for the function
        symTableItem = STableInsertFunction(globalSymTable, name);

        // create new sym table
        STableInit(currentSymTable);

        // create list of parameters
        tDLList *parameters = malloc(sizeof(tDLList));
        DLInitList(parameters);
        symTableItem->data->parameters = parameters;
    }
}

/**
 * @brief Add new parameter into stack of function's parameters
 * @param name
 */
void addParam(char *name)
{
    // global table defined
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return;
    }

    // not in function
    if (currentSymTable == NULL || tempSymTable->parameters == NULL) {
        error_fatal(ERROR_SEMANTIC_OTHER);
        return;
    }

    // create new parameter
    tParameter *parameter = malloc(sizeof(tParameter));
    if (parameter == NULL) {
        error_fatal(ERROR_INTERNAL);
        return;
    }

    // allocate memory for parameter name
    parameter->name = malloc(strlen(name) + 1);
    if (parameter->name == NULL) {
        error_fatal(ERROR_INTERNAL);
        return;
    }

    strcpy(parameter->name, name);

    // push parameter on the stack
    stackPush(tempSymTable->parameters, parameter);
}
