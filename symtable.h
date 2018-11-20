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

#ifndef SYMTABLE_HEADER
#define SYMTABLE_HEADER

#include <stdbool.h>
#include "list.h"

typedef enum {
	TYPE_VARIABLE,
	TYPE_FUNCTION
} BTNodeType;

typedef enum {
	TYPE_INTEGER,
	TYPE_DOUBLE,
	TYPE_STRING
} BTVariableType;

typedef struct sBTVariableData {
	char *key;
	BTVariableType type;
}	BTVariableData;

typedef struct sBTFunctionData {
	char *key;
	BTVariableType type;
	tDLList *params; // BTVariableData[]
	bool defined;
	bool declared;
} BTFunctionData;

typedef struct sBTNode {
	char* key;
	BTNodeType type;
	void *data;
	struct sBTNode *LPtr;
	struct sBTNode *RPtr;
} *BTNodePtr;

typedef struct sSTable {
	BTNodePtr root;
} STable;

void BTInit   (BTNodePtr *);
BTNodePtr BTSearch  (BTNodePtr, char *);
void BTInsert (BTNodePtr *, char *, BTNodeType, void *);
void ReplaceByRightmost (BTNodePtr, BTNodePtr *);
void BTDelete (BTNodePtr *, char *);
void BTDispose(BTNodePtr *);

void STableInit(STable *);
void STableInsertVariable(STable *, char *, BTVariableType);
void STableInsertFunction(STable *, char *, BTVariableType, tDLList *, bool, bool);
BTNodePtr STSearch(STable *, char *);
void STDelete(STable *, char *);
void STDispose(STable *);

#endif
