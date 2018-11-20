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
BTNodePtr currentFunction; // item from the global symbol table, currently created function

/**
 * @brief Creates new global table
 */
void initGlobalSymTable()
{
    currentSymTable = NULL;
    currentFunction = NULL;

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

    currentFunction = STSearch(globalSymTable, name);

    // is the function in the global sym table?
    if (currentFunction != NULL) {
        // the symbol is declared, but is not a function
        if (currentFunction->type != TYPE_FUNCTION) {
            error_fatal(ERROR_SEMANTIC_DEF);
            return;
        }

        // the function is defined yet
        if (currentFunction->defined) {
            error_fatal(ERROR_SEMANTIC_DEF);
            return;
        }
    } else {
        // the function is not in global sym table

        // add function into global table
        // todo create data for the function
        currentFunction = STableInsertFunction(globalSymTable, name);

        // create new sym table
        STableInit(currentSymTable);

        // create list of parameters
        tDLList *parameters = malloc(sizeof(tDLList));
        DLInitList(parameters);
        currentFunction->data->parameters = parameters;
    }
}

/**
 * @brief Add new parameter into list of function's parameters
 * @param name
 */
void addParam(char *name)
{
    // global table defined
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return;
    }

    // make sure we're in a function
    if (currentSymTable == NULL || currentFunction == NULL || currentFunction->data->parameters == NULL) {
        error_fatal(ERROR_SEMANTIC_OTHER);
        return;
    }

    // create new parameter
    // allocate memory for parameter name
    char *param = malloc(strlen(name) + 1);
    if (param == NULL) {
        error_fatal(ERROR_INTERNAL);
        return;
    }

    strcpy(parameter->name, name);

    // add new parameter to the list
    DLInsertLast(currentFunction->data->parameters, (void *) param);
}

/**
 * @brief Create new variable,
 * @param name
 */
void addVar(char *name)
{
    // alloc mem for name string
    char *var = malloc(strlen(name) + 1);
    if (var == NULL) {
        error_fatal(ERROR_INTERNAL);
        return;
    }

    strcpy(var, name);

    if (currentFunction == NULL) {
        // if is not in a function definition, add new global variable
        STableInsertVariable(globalSymTable, var); // todo: var type in symbol table...?
    } else {
        // if is in a function definition, add new local variable
        STableInsertVariable(currentSymTable, var); // todo: var type in symbol table...?
    }
}

/**
 * @brief End of function declaration or definition
 */
void endFunction()
{
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return;
    }

    if (currentSymTable == NULL || currentFunction == NULL) {
        // make sure we're in a function
        error_fatal(ERROR_SEMANTIC_OTHER);
        return;
    }

    currentFunction->data->localSymTab = currentSymTable;
}
