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

#include "semantic.h"
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
