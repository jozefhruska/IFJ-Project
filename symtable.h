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

/**
 * @brief  Structure representing type of sBTNode.
 */
typedef enum {
	TYPE_VARIABLE,
	TYPE_FUNCTION
} BTNodeType;

/**
 * @brief  Structure representing variable data type.
 */
typedef enum {
	TYPE_INTEGER,
	TYPE_DOUBLE,
	TYPE_STRING
} BTVariableDataType;

/**
 * @brief  Structure representing variable.
 */
typedef struct sBTVariableData {
	char *key;
	BTVariableDataType type;
} * BTVariableData;

/**
 * @brief  Structure representing function.
 */
typedef struct sBTFunctionData {
	char *key;
	bool defined;
	bool declared;
	ListItem parameters;
} *BTFunction;

/**
 * @brief  Structure representing one node of Binary Search Tree.
 */
typedef struct sBTNode {
	char *key;
	BTNodeType type;
	void* data;
	struct sBTNode *LBTNode;
	struct sBTNode *RBTNode;
} *BTNode;

#endif SYMTABLE_HEADER