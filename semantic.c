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


void initGlobalSymTable() {
    currentFunction = NULL;

    // init global symbol table
    STableInit(globalSymTable);
}

void addFunction(char *name) {
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
        STableInsertFunction(globalSymTable, name,
                             paramList); // TODO: set declared true, defined false, remove variable type
    }
}

void addParam(char *name) {
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

void addVar(char *name) {
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

void endFunction() {
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return;
    }

    // make sure we're in a function
    if (currentFunction == NULL) {
        error_fatal(ERROR_SEMANTIC_OTHER);
        return;
    }

    // all good, exit the function
    currentFunction = NULL;
}

void functionDefinition(char *name) {
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return;
    }

    // search for the function
    BTNodePtr func = STSearch(globalSymTable, name);

    // the function doesn't exist
    if (func == NULL) {
        error_fatal(ERROR_SEMANTIC_DEF);
        return;
    }

    // if not a function
    if (func->type != TYPE_FUNCTION) {
        error_fatal(ERROR_SEMANTIC_DEF);
        return;
    }

    SEM_DATA_FUNCTION(func)->defined = true;
}

bool isFunctionDefined(char *name) {
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return false;
    }

    // search for the function
    BTNodePtr func = STSearch(globalSymTable, name);

    // the function doesn't exist
    if (func == NULL) {
        error_fatal(ERROR_SEMANTIC_DEF);
        return;
    }

    // if not a function
    if (func->type != TYPE_FUNCTION) {
        return false;
    }

    return SEM_DATA_FUNCTION(func)->defined;
}

bool isFunctionDeclared(char *name) {
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return false;
    }

    // search for the function
    BTNodePtr func = STSearch(globalSymTable, name);

    // the function doesn't exist
    if (func == NULL) {
        return false;
    }

    // if not a function
    if (func->type != TYPE_FUNCTION) {
        return false;
    }

    return true;
}

bool isVarDeclared(char *name) {
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return false;
    }

    // search for the variable
    BTNodePtr variable = STSearch(globalSymTable, name);

    if (variable == NULL) {
        return false;
    }

    // if not a variable
    if (variable->type != TYPE_VARIABLE) {
        return false;
    }

    return true;
}

BTVariableData *getVar(char *name) {
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return NULL;
    }

    // search for the variable
    BTNodePtr variable = STSearch(globalSymTable, name);

    if (variable == NULL) {
        return NULL;
    }

    // if not a variable
    if (variable->type != TYPE_VARIABLE) {
        return NULL;
    }

    return SEM_DATA_VARIABLE(variable);
}

bool isParamDeclared(char *functionName, char *paramName) {
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return false;
    }

    // search for the function
    BTNodePtr func = STSearch(globalSymTable, functionName);

    // function doesn't exist
    if (func == NULL) {
        error_fatal(ERROR_SEMANTIC_DEF);
        return false;
    }

    // search for the parameter in the function
    tDLList *paramList = SEM_DATA_FUNCTION(func)->params;

    if (paramList == NULL) {
        error_fatal(ERROR_INTERNAL);
        return false;
    }

    bool found = DLSearchString(paramList, paramName);

    return found;
}

BTVariableData *getParam(char *functionName, char *paramName) {
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return NULL;
    }

    // search for the function
    BTNodePtr func = STSearch(globalSymTable, functionName);

    // function doesn't exist
    if (func == NULL) {
        error_fatal(ERROR_SEMANTIC_DEF);
        return NULL;
    }

    // search for the parameter in the function
    tDLList *paramList = SEM_DATA_FUNCTION(func)->params;

    if (paramList == NULL) {
        error_fatal(ERROR_INTERNAL);
        return NULL;
    }

    bool found = DLSearchString(paramList, paramName);

    if (found == FALSE) {
        return NULL;
    }

    return (BTVariableData *) paramList->Act->data;
}
