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

#include "error_handler.h"
#include "list.h"

/**
 * @brief  Structure representing type of node in a Binary Table.
 */
typedef enum {
	TYPE_VARIABLE,
	TYPE_FUNCTION
} BTNodeType;

/**
 * @brief Structure for parameters of a function
 */
typedef struct {
	char *name;
	bool isParameter; // true - is parameter, false - is local variable
} BTFunctionParam;

/**
 * @brief  Structure additional function data in a Binary Table node.
 */
typedef struct sBTFunctionData {
	tDLList *params; // BTFunctionParam[]
	bool defined;
	bool declared;
} BTFunctionData;

/**
 * @brief  Structure representing node of a Binary Table.
 */
typedef struct sBTNode {
	char* key;
	BTNodeType type;
	BTFunctionData *data;
	struct sBTNode *LPtr;
	struct sBTNode *RPtr;
} *BTNodePtr;

/**
 * @brief  Structure representing a Table of Symbols.
 */
typedef struct sSTable {
	BTNodePtr root;
} STable;

/**
 * @brief  Initializes a Binary Table.
 * @note   Sets initial node to NULL
 * @param  *node: Initial node
 * @retval None
 */
void BTInit   (BTNodePtr *node);

/**
 * @brief  Searches for node in a Binary Table.
 * @param  node: Node from which searching starts.
 * @param  *key: Name of node to find.
 * @retval Pointer to node if found, NULL if not.
 */
BTNodePtr BTSearch  (BTNodePtr node, char *key);

/**
 * @brief  Inserts node into a Binary Table.
 * @param  *node: Node under which should the new one inserted.
 * @param  *key: Name of new node.
 * @param  type: Type of new node. (Function/Variable)
 * @param  *data: If node is of type function, points to it's additional data. If variable, should be NULL.
 * @retval None
 */
void BTInsert (BTNodePtr *node, char *key, BTNodeType type, BTFunctionData *data);

/**
 * @brief  Replaces the most-right node in a Binary Table.
 * @param  PtrReplaced: Pointer to node, which is to be replaced.
 * @param  *node: Pointer to node which should the target node.
 * @retval None
 */
void ReplaceByRightmost (BTNodePtr PtrReplaced, BTNodePtr *node);

/**
 * @brief  Deletes node of a Binary Table.
 * @param  *node: Node from which searching starts.
 * @param  *key: Name of node that should be deleted.
 * @retval None
 */
void BTDelete (BTNodePtr *node, char *key);

/**
 * @brief  Deletes whole Binary Tree.
 * @note   All used emory is freed.
 * @param  *node: Node from which deletion starts.
 * @retval None
 */
void BTDispose(BTNodePtr *node);

/**
 * @brief  INTERFACE - Initializes a Table of Symbols.
 * @note   Sets initial node to NULL
 * @param  *table: Table to be initialized.
 * @retval None
 */
void STableInit(STable *table);

/**
 * @brief  INTERFACE - Searches for node in a Table of Symbols.
 * @param  node: Table to search.
 * @param  *key: Name of node to find.
 * @retval Pointer to node if found, NULL if not.
 */
BTNodePtr STableSearch(STable *table, char *key);

/**
 * @brief  INTERFACE - Inserts node into a Table of Symbols.
 * @param  *node: Table to which new node should be inserted.
 * @param  *key: Name of new node.
 * @param  type: Type of new node. (Function/Variable)
 * @param  *data: If node is of type function, points to it's additional data. If variable, should be NULL.
 * @retval None
 */
void STableInsert(STable *table, char *key, BTNodeType type);

/**
 * @brief  INTERFACE - Deletes node of a Table of Symbols.
 * @param  *node: Table where target node should be located.
 * @param  *key: Name of node that should be deleted.
 * @retval None
 */
void STableDelete(STable *table, char *key);

/**
 * @brief  INTERFACE - Deletes whole Table of Symbols.
 * @note   All used emory is freed.
 * @param  *node: Table to be deleted.
 * @retval None
 */
void STableDispose(STable *table);

#endif
