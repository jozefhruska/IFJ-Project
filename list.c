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

#include <stdbool.h>
#include <string.h>
#include "list.h"

int errflg;
int solved;

void DLError() {
	printf("*ERROR* The program has performed an illegal operation.\n");
	errflg = TRUE; /* globální proměnná -- příznak ošetření chyby */
	return;
}

void DLInitList(tDLList *L) {
	if (!L) return;

	L->First = NULL;
	L->Last = NULL;
	L->Act = NULL;
}

void DLDisposeList(tDLList *L) {
	if (!L) return;

	tDLElemPtr tmp;

	while ((tmp = L->First) != NULL) {
		L->First = L->First->rptr;
		free(tmp);
	}

	L->First = NULL;
	L->Last = NULL;
	L->Act = NULL;
}

void DLInsertFirst(tDLList *L, void *data) {
	if (!L) return;

	tDLElemPtr created = malloc(sizeof(struct tDLElem));

	if (created == NULL) {
		DLError();
		return;
	}

	created->data = data;
	created->rptr = L->First;
	created->lptr = NULL;

	if (L->First != NULL) L->First->lptr = created;
	else L->Last = created;

	L->First = created;
}

void DLInsertLast(tDLList *L, void *data) {
	if (!L) return;

	tDLElemPtr created = malloc(sizeof(struct tDLElem));

	if (created == NULL) {
		DLError();
		return;
	}

	created->data = data;
	created->lptr = L->Last;
	created->rptr = NULL;

	if (L->Last != NULL) L->Last->rptr = created;
	else L->First = created;

	L->Last = created;
}

void DLFirst(tDLList *L) {
	L->Act = L->First;
}

void DLLast(tDLList *L) {
	L->Act = L->Last;
}

void DLCopyFirst(tDLList *L, void *data) {
	if (!L || !data) return;

	if (L->First == NULL) {
		DLError();
		return;
	}

	data = L->First->data;
}

void DLCopyLast(tDLList *L, void *data) {
	if (!L || !data) return;

	if (L->Last == NULL) {
		DLError();
		return;
	}

	data = L->Last->data;
}

void DLDeleteFirst(tDLList *L) {
	if (!L) return;

	if (L->First == NULL) return;
	if (L->Act == L->First) L->Act = NULL;

	tDLElemPtr tmp = L->First->rptr;
	free(L->First);
	L->First = tmp;

	if (tmp) tmp->lptr = NULL;
	else L->Last = NULL;
}

void DLDeleteLast(tDLList *L) {
	if (!L) return;

	if (L->Last == NULL)return;
	if (L->Act == L->Last) L->Act = NULL;

	tDLElemPtr tmp = L->Last->lptr;
	free(L->Last);
	L->Last = tmp;

	if (tmp) tmp->rptr = NULL;
	else L->First = NULL;
}

void DLPostDelete(tDLList *L) {

	if (!L) return;

	if (L->Act == NULL || L->Last == L->Act) return;

	tDLElemPtr tmp = L->Act->rptr->rptr;
	free(L->Act->rptr);

	L->Act->rptr = tmp;

	if (tmp != NULL) tmp->lptr = L->Act;
	else L->Last = L->Act;
}

void DLPreDelete(tDLList *L) {
	if (!L) return;

	if (L->Act == NULL || L->First == L->Act) return;

	tDLElemPtr tmp = L->Act->lptr->lptr;
	free(L->Act->lptr);

	L->Act->lptr = tmp;

	if (tmp != NULL) tmp->rptr = L->Act;
	else L->First = L->Act;
}

void DLPostInsert(tDLList *L, void *data) {
	if (!L) return;

	if (L->Act == NULL) return;

	tDLElemPtr created = malloc(sizeof(struct tDLElem));

	if (created == NULL) {
		DLError();
		return;
	}

	created->data = data;
	created->lptr = L->Act;
	created->rptr = L->Act->rptr;

	if (L->Act->rptr != NULL) L->Act->rptr->lptr = created;
	else L->Last = created;

	L->Act->rptr = created;
}

void DLPreInsert(tDLList *L, void *data) {

	if (!L) return;

	if (L->Act == NULL) return;

	tDLElemPtr created = malloc(sizeof(struct tDLElem));

	if (created == NULL) {
		DLError();
		return;
	}

	created->data = data;
	created->rptr = L->Act;
	created->lptr = L->Act->lptr;

	if (L->Act->lptr != NULL) L->Act->lptr->rptr = created;
	else L->First = created;

	L->Act->lptr = created;
}

void DLCopy(tDLList *L, void *data) {
	if (!L || !data) return;

	if (L->Act == NULL) {
		DLError();
		return;
	}

	data = L->Act->data;
}

void DLActualize(tDLList *L, void *data) {
	if (!L) return;

	if (L->Act == NULL) return;

	L->Act->data = data;
}

void DLSucc(tDLList *L) {
	if (!L) return;

	if (L->Act == NULL) return;

	L->Act = L->Act->rptr;
}

void DLPred(tDLList *L) {
	if (!L) return;

	if (L->Act == NULL) return;

	L->Act = L->Act->lptr;
}

int DLActive(tDLList *L) {
	return (L->Act) ? 1 : 0;
}
