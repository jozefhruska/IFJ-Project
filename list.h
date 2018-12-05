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

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define FALSE 0
#define TRUE 1

#ifndef LIST_HEADER
#define LIST_HEADER

extern int errflg;
extern int solved;

typedef struct tDLElem {
        void *data;
        struct tDLElem *lptr;
        struct tDLElem *rptr;
} *tDLElemPtr;

typedef struct {
    tDLElemPtr First;
    tDLElemPtr Act;
    tDLElemPtr Last;
} tDLList;

void DLInitList (tDLList *);
void DLDisposeList (tDLList *);
void DLInsertFirst (tDLList *, void *);
void DLInsertLast(tDLList *, void *);
void DLFirst (tDLList *);
void DLLast (tDLList *);
void DLCopyFirst (tDLList *, void *);
void DLCopyLast (tDLList *, void *);
void DLDeleteFirst (tDLList *);
void DLDeleteLast (tDLList *);
void DLPostDelete (tDLList *);
void DLPreDelete (tDLList *);
void DLPostInsert (tDLList *, void *);
void DLPreInsert (tDLList *, void *);
void DLCopy (tDLList *, void *);
void DLActualize (tDLList *, void *);
void DLSucc (tDLList *);
void DLPred (tDLList *);
int DLActive (tDLList *);
tDLElemPtr DLPopFirst(tDLList *L);
bool DLSearchString(tDLList *List, char *string);

// InstructionPtr
void DLFindInstruction(tDLList *List, char *instructionName);

#endif
