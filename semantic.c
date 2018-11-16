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

tSymbolTable *globalSymTable; // global symbol table
tSymbolTable *tempSymTable; // temporary symbol table
tSymbolTable *currentSymTable; // current local symbol table
tSymbolTableStack *symTableStack; // stack of local symbol talbes

/**
 * @brief Creates new global table
 */
void initGlobalSymTable()
{
    globalSymTable = NULL;
    tempSymTable = NULL;
    currentSymTable = NULL;
    symTableStack = NULL;

    // init global symbol table
    tableInit(globalSymTable);
}

/**
 * @brief Start of creating new function, or it's declaration
 * @param name
 */
void addFunction(char *name)
{
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
    }

    tData *symTableItem = tableSearch(globalSymTable, name);

    // is the function in the global sym table?
    if (symTableItem != NULL) {
        // the symbol is declared, but is not a function
        if (isFunction(symTableItem) == false) {
            error_fatal(ERROR_SEMANTIC_DEF);
            return;
        }

        // the function is declared and defined yut
        if (isDeclared(symTableItem) && isDefined(symTableItem)) {
            error_fatal(ERROR_SEMANTIC_DEF);
            return;
        }
    } else {
        // the function is not in global sym table

        // add function into global table
        symTableItem = tableInsert(globalSymTable, name, TYPE_FUNCTION);
        symTableItem->declared = true;
        symTableItem->defined = false;

        // null parameters
        tableInit(tempSymTable);
        tempSymTable->parameters = stackInit();
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
    if (tempSymTable == NULL || tempSymTable->parameters == NULL) {
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
