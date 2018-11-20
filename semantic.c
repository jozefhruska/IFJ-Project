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

/**
 * Macro for casting data attribute from function symtable item
 */
#define SEM_DATA_FUNCTION(tabItem) ((BTFunctionData *)(tabItem->data))

/**
 * Macro for casting data attribute from variable symtable item
 */
#define SEM_DATA_VARIABLE(tabItem) ((BTVariableData *)(tabItem->data))

STable *globalSymTable; // global symbol table
BTNodePtr currentFunction; // item from the global symbol table, currently created function

/**
 * @brief Creates new global table
 */
void initGlobalSymTable()
{
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

    if (currentFunction == NULL) {
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
        if (SEM_DATA_FUNCTION(currentFunction)->defined) {
            error_fatal(ERROR_SEMANTIC_DEF);
            return;
        }
    } else {
        // the function is not in global sym table

        // create list empty list of parameters
        tDLList *paramList = malloc(sizeof(tDLList));
        if (paramList == NULL) {
            error_fatal(ERROR_INTERNAL);
            return;
        }

        DLInitList(paramList);

        // add function into global table
        STableInsertFunction(globalSymTable, name, paramList); // TODO: set declared true, defined false, remove variable type
    }
}

/**
 * @brief Add new parameter into list of function's parameters
 * @pre First call addFunction()
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
    if (currentFunction == NULL || SEM_DATA_FUNCTION(currentFunction)->params == NULL) {
        error_fatal(ERROR_SEMANTIC_OTHER);
        return;
    }

    // create new parameter
    // allocate memory for parameter
    BTVariableData *param = malloc(sizeof(BTVariableData));
    if (param == NULL) {
        error_fatal(ERROR_INTERNAL);
        return;
    }

    param->key = name;

    // add new parameter to the list
    DLInsertLast(SEM_DATA_FUNCTION(currentFunction)->params, (void *) param);
}

/**
 * @brief Create new variable,
 * @param name
 */
void addVar(char *name)
{
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return;
    }

    // if in a function, add it as a parameter
    if (currentFunction != NULL) {
        addParam(name);
        return;
    }

    // in global
    STableInsertVariable(globalSymTable, name);
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
