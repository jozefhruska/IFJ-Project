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

#include <string.h>

#include "symtable.h"

void BTInit(BTNodePtr *node) {
	(* node) = NULL;
}

BTNodePtr BTSearch(BTNodePtr node, char *key) {
	if (node != NULL) {
		if (strcmp(key, node->key) < 0) return BTSearch(node->LPtr, key);
		else if (strcmp(key, node->key) > 0) return BTSearch(node->RPtr, key);
		else return node;
	} else return NULL;
}

void BTInsert(BTNodePtr *node, char *key, BTNodeType type, BTFunctionData *data) {
	if (*node != NULL) {
		if (strcmp(key, (* node)->key) < 0) {
			BTInsert(&(* node)->LPtr, key, type, data);
			return;
		} else if (strcmp(key, (* node)->key) > 0) {
			BTInsert(&(* node)->RPtr, key, type, data);
			return;
		} else (* node)->data = data;
	} else {
		if ((*node = malloc(sizeof(struct sBTNode))) != NULL) {
			(* node)->key = key;
			(* node)->type = type;
			(* node)->data = data;
			(* node)->LPtr = NULL;
			(* node)->RPtr = NULL;
		} else return;
	}
}

void ReplaceByRightmost (BTNodePtr PtrReplaced, BTNodePtr *node) {
	if ((* node)->RPtr != NULL) ReplaceByRightmost(PtrReplaced, &((* node)->RPtr));
	else {
		PtrReplaced->key = (* node)->key;
		PtrReplaced->type = (* node)->type;
		PtrReplaced->data = (* node)->data;

		BTNodePtr tempNode = *node;
		*node = (* node)->LPtr;
		free(tempNode);
	}
}

void BTDelete(BTNodePtr *node, char *key) {
	if ((* node) != NULL) {
		if (strcmp((* node)->key, key) > 0) BTDelete(&((* node)->LPtr), key);
		else if (strcmp((* node)->key, key) < 0) BTDelete(&((* node)->RPtr), key);
		else {
			if (((* node)->LPtr == NULL) && ((* node)->RPtr == NULL)) {
					free(*node);
					*node = NULL;
			} else if (((* node4)->LPtr != NULL) && ((* node)->RPtr == NULL)) {
					BTNodePtr itemToDelete = *node;
					*node = (* node)->LPtr;
					free(itemToDelete);
			} else if (((* node)->LPtr == NULL) && ((* node)->RPtr != NULL)) {
					BTNodePtr itemToDelete = *node;
					*node = (* node)->RPtr;
					free(itemToDelete);
			} else ReplaceByRightmost((* node), &((* node)->LPtr));
		}
	}
}

void BTDispose(BTNodePtr *node) {
	if ((* node) != NULL) {
		if ((* node)->type == TYPE_FUNCTION && (* node)->data->params != NULL) {
			DLDisposeList((* node)->data->params);
		}

		BTDispose(&(* node)->LPtr);
		BTDispose(&(* node)->RPtr);

		free(*node);
		*node = NULL;
	}
}

void STableInit(STable *table) {
	BTInit(&(table->root));

	BTFunctionData *functionData;
	tDLList *params;

	/* Built-in function - inputs() */
	STableInsert(table, "inputs", TYPE_FUNCTION);
	functionData = (BTFunctionData *) STableSearch(table, "inputs")->data;

	if (functionData != NULL) {
		DLInitList(params);

		functionData->params = params;
		functionData->defined = TRUE;
		functionData->declared = TRUE;
	}

	/* Built-in function - inputi() */
	STableInsert(table, "inputi", TYPE_FUNCTION);
	functionData = (BTFunctionData *) STableSearch(table, "inputi")->data;

	if (functionData != NULL) {
		DLInitList(params);

		functionData->params = params;
		functionData->defined = TRUE;
		functionData->declared = TRUE;
	}

	/* Built-in function - inputi() */
	STableInsert(table, "inputf", TYPE_FUNCTION);
	functionData = (BTFunctionData *) STableSearch(table, "inputf")->data;

	if (functionData != NULL) {
		DLInitList(params);

		functionData->params = params;
		functionData->defined = TRUE;
		functionData->declared = TRUE;
	}

	/* Built-in function - print() */
	STableInsert(table, "print", TYPE_FUNCTION);
	functionData = (BTFunctionData *) STableSearch(table, "print")->data;

	if (functionData != NULL) {
		DLInitList(params);

		functionData->params = params; /* TODO: print() function params */
		functionData->defined = TRUE;
		functionData->declared = TRUE;
	}

	/* Built-in function - length(s) */
	STableInsert(table, "length", TYPE_FUNCTION);
	functionData = (BTFunctionData *) STableSearch(table, "length")->data;
	params = malloc(sizeof(tDLList));

	if (functionData != NULL && params != NULL) {
		DLInitList(params);
		DLInsertLast(params, "s");

		functionData->params = params;
		functionData->defined = TRUE;
		functionData->declared = TRUE;
	}

	/* Built-in function - substr(s, i, n) */
	STableInsert(table, "substr", TYPE_FUNCTION);
	functionData = (BTFunctionData *) STableSearch(table, "substr")->data;
	params = malloc(sizeof(tDLList));

	if (functionData != NULL && params != NULL) {
		DLInitList(params);
		DLInsertLast(params, "s");
		DLInsertLast(params, "i");
		DLInsertLast(params, "n");

		functionData->params = params;
		functionData->defined = TRUE;
		functionData->declared = TRUE;
	}

	/* Built-in function - ord(s, i) */
	STableInsert(table, "ord", TYPE_FUNCTION);
	functionData = (BTFunctionData *) STableSearch(table, "ord")->data;
	params = malloc(sizeof(tDLList));

	if (functionData != NULL && params != NULL) {
		DLInitList(params);
		DLInsertLast(params, "s");
		DLInsertLast(params, "i");

		functionData->params = params;
		functionData->defined = TRUE;
		functionData->declared = TRUE;
	}

	/* Built-in function - chr(i) */
	STableInsert(table, "chr", TYPE_FUNCTION);
	functionData = (BTFunctionData *) STableSearch(table, "chr")->data;
	params = malloc(sizeof(tDLList));

	if (functionData != NULL && params != NULL) {
		DLInitList(params);
		DLInsertLast(params, "i");

		functionData->params = params;
		functionData->defined = TRUE;
		functionData->declared = TRUE;
	}

}

void STableInsert(STable *table, char *key, BTNodeType type) {
	if (type == TYPE_VARIABLE) {
		BTInsert(&(table->root), key, type, NULL);
	} else {
		BTFunctionData *functionData;

		if ((functionData = malloc(sizeof(struct sBTFunctionData))) != NULL) {
			tDLList *params;

			if ((params = malloc(sizeof(tDLList))) != NULL) {
				DLInitList(params);

				functionData->params = params;
				functionData->defined = false;
				functionData->declared = false;

				BTInsert(&(table->root), key, type, functionData);
			} else {
				BTDispose(&(table->root));
				error_fatal(ERROR_INTERNAL);
			}
		} else {
			BTDispose(&(table->root));
			error_fatal(ERROR_INTERNAL);
		}
	}
}

BTNodePtr STableSearch(STable *table, char *key) {
	return BTSearch(table->root, key);
}

void STableDelete(STable *table, char *key) {
	BTDelete(&(table->root), key);
}

void STableDispose(STable *table) {
	BTDispose(&(table->root));
}
