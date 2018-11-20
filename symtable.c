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

#include "symtable.h"

void BTInit(BTNodePtr *node) {
	(* node) = NULL;
}

BTNodePtr BTSearch(BTNodePtr node, char *key) {
	if (node != NULL) {
		if (node->key > key) return BTSearch(node->LPtr, key);
		else if (node->key < key) return BTSearch(node->RPtr, key);
		else return node;
	} else return NULL;
}

void BTInsert(BTNodePtr *node, char *key, BTNodeType type, void *data) {
	if (*node != NULL) {
		if ((* node)->key > key) {
			BTInsert(&(* node)->LPtr, key, type, data);
			return;
		} else if ((* node)->key < key) {
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
		if ((* node)->key > key) BTDelete(&((* node)->LPtr), key);
		else if ((* node)->key < key) BTDelete(&((* node)->RPtr), key);
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
		BTDispose(&(* node)->LPtr);
		BTDispose(&(* node)->RPtr);

		free(*node);
		*node = NULL;
	}
}

void STableInit(STable *table) {
	BTInit(&(table->root));
}


