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

#include "symtable.c"

/**
 * @brief  Structure representing item of a two-way list of strings.
 */
typedef struct sListItem {
	BTVariableData data;
	struct sListItem *prevItem;
	struct sListItem *nextItem;
} *ListItem;

/**
 * @brief  Structure representing two-way list of strings.
 */
typedef struct sList {
    ListItem First;
    ListItem Last;
} *List;

void listInit (List);
void listDispose (List);
void listInsert(List, char*, BTVariableDataType);