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

    if (currentFunction != NULL) {
        // current function was not finished!
        // can't define function inside another function
        error_fatal(ERROR_SEMANTIC_OTHER);
        return;
    }

    BTNodePtr func = STableSearch(globalSymTable, name);

    // is the function in the global sym table?
    if (func != NULL) {
        // the symbol is declared, but is not a function
        if (func->type != TYPE_FUNCTION) {
            error_fatal(ERROR_SEMANTIC_DEF);
            return;
        }

        // the function is defined yet
        if (func->data->defined) {
            error_fatal(ERROR_SEMANTIC_DEF);
            return;
        }

        currentFunction = func;
    } else {
        // the function is not in global sym table

        // add function into global table
        STableInsert(globalSymTable, name, TYPE_FUNCTION);

        // create list empty list of parameters
        tDLList *paramList = malloc(sizeof(tDLList));
        if (paramList == NULL) {
            error_fatal(ERROR_INTERNAL);
            return;
        }

        DLInitList(paramList);

        // add params and default values
        func = STableSearch(globalSymTable, name);

        // can't insert into global sym table
        if (func == NULL) {
            error_fatal(ERROR_INTERNAL);
            return;
        }

        func->data->params = paramList;
        func->data->defined = false;
        func->data->declared = true;

        currentFunction = func;
    }
}

void addParam(char *name) {
    // global table defined
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return;
    }

    // make sure we're in a function
    if (currentFunction == NULL || currentFunction->data->params == NULL) {
        error_fatal(ERROR_SEMANTIC_OTHER);
        return;
    }

    // add new parameter to the list
    DLInsertLast(currentFunction->data->params, (void *) name);
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

BTVariableData *getNthParam(char *functionName, unsigned int n) {
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

    // not a function
    if (func->type != TYPE_FUNCTION) {
        error_fatal(ERROR_SEMANTIC_DEF);
        return NULL;
    }

    tDLList *paramList = SEM_DATA_FUNCTION(func)->params;

    // list is ok
    if (paramList == NULL) {
        error_fatal(ERROR_INTERNAL);
        return NULL;
    }

    unsigned int i = 0; // current index
    DLFirst(paramList); // go to the first param

    while (i < n) {
        if (paramList->Act == paramList->Last) {
            break;
        } else {
            DLSucc(paramList);
        }

        i++;
    }

    // if found
    if (i == n) {
        return (BTVariableData *) paramList->Act;
    }

    return NULL;
}

bool eachFunctionDefined() {
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return false;
    }

    return eachFunctionInTreeDefined(globalSymTable);
}

/**
 * @brief Checks if each function in the tree is defined - preorder
 * @param root Pointer to the root
 * @return true if each function in tree is defined, else otherwise
 */
bool eachFunctionInTreeDefined(BTNodePtr root) {
    if (root == NULL) {
        return true;
    }

    if (root->type == TYPE_FUNCTION && SEM_DATA_FUNCTION(root)->defined == false) {
        return false;
    }

    return eachFunctionInTreeDefined(root->LPtr) && eachFunctionInTreeDefined(root->RPtr);
}
