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


BTNodePtr currentFunction; // item from the global symbol table, currently created function


void initGlobalSymTable() {
    currentFunction = NULL;

    // init global symbol table
    globalSymTable = malloc(sizeof(STable));
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

void addParam(char *name, bool isParam) {
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

    // make sure param doesn't exist
    if (isParamDeclared(currentFunction->key, name)) {
        error_fatal(ERROR_SEMANTIC_DEF);
        return;
    }

    // add new parameter to the list
    BTFunctionParam *param = malloc(sizeof(BTFunctionParam));
    if (param == NULL) {
        error_fatal(ERROR_INTERNAL);
        return;
    }

    param->name = name;
    param->isParameter = isParam;

    DLInsertLast(currentFunction->data->params, (void *) param);
}

void addVar(char *name) {
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return;
    }

    // if in a function, can't add global variable
    if (currentFunction != NULL) {
        error_fatal(ERROR_SEMANTIC_OTHER);
        return;
    }

    // in global
    STableInsert(globalSymTable, name, TYPE_VARIABLE);
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
    BTNodePtr func = STableSearch(globalSymTable, name);

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

    func->data->defined = true;
}

bool isFunctionDefined(char *name) {
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return false;
    }

    // search for the function
    BTNodePtr func = STableSearch(globalSymTable, name);

    // the function doesn't exist
    if (func == NULL) {
        error_fatal(ERROR_SEMANTIC_DEF);
        return false;
    }

    // if not a function
    if (func->type != TYPE_FUNCTION) {
        error_fatal(ERROR_SEMANTIC_DEF);
        return false;
    }

    return func->data->defined;
}

bool isFunctionDeclared(char *name) {
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return false;
    }

    // search for the function
    BTNodePtr func = STableSearch(globalSymTable, name);

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
    BTNodePtr variable = STableSearch(globalSymTable, name);

    if (variable == NULL) {
        return false;
    }

    // if not a variable
    if (variable->type != TYPE_VARIABLE) {
        return false;
    }

    return true;
}

bool isParamDeclared(char *functionName, char *paramName) {
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return false;
    }

    // search for the function
    BTNodePtr func = STableSearch(globalSymTable, functionName);

    // function doesn't exist
    if (func == NULL || func->type != TYPE_FUNCTION) {
        error_fatal(ERROR_SEMANTIC_DEF);
        return false;
    }

    // search for the parameter in the function
    tDLList *paramList = func->data->params;

    if (paramList == NULL) {
        error_fatal(ERROR_INTERNAL);
        return false;
    }

    bool found = DLSearchParam(paramList, paramName);

    return found;
}

bool DLSearchParam(tDLList *List, char *string) {
    // go to the first item
    DLFirst(List);

    // for each item in the list
    while ((List->Act != List->Last && List->Act != NULL) || (List->Act == List->Last && List->Act != NULL) ) {
        // if the active node is the wanted one
        if (strcmp(((BTFunctionParam *) List->Act->data)->name, string) == 0) {
            return true;
        }

        // move to the next item
        DLSucc(List);
    }

    return false;
}

char *getNthParam(char *functionName, unsigned int n) {
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return NULL;
    }

    // search for the function
    BTNodePtr func = STableSearch(globalSymTable, functionName);

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

    tDLList *paramList = func->data->params;

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
    if (i == n && paramList->Act != NULL) {
        return ((BTFunctionParam *) paramList->Act->data)->name;
    }

    return NULL;
}

bool eachFunctionDefined() {
    if (globalSymTable == NULL) {
        error_fatal(ERROR_INTERNAL);
        return false;
    }

    return eachFunctionInTreeDefined(globalSymTable->root);
}

bool eachFunctionInTreeDefined(BTNodePtr root) {
    if (root == NULL) {
        return true;
    }

    if (root->type == TYPE_FUNCTION && root->data->defined == false) {
        return false;
    }

    return eachFunctionInTreeDefined(root->LPtr) && eachFunctionInTreeDefined(root->RPtr);
}
