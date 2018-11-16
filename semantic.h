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

#ifndef IFJ_PROJECT_SEMANTIC_H
#define IFJ_PROJECT_SEMANTIC_H

/**
 * @brief Union representing any data
 */
typedef union {
    int i;
    float f;
    char *s;
} tDataValue;

/**
 * @brief Types of any data enumeration
 */
typedef enum {
    INTEGER,
    FLOAT,
    STRING
} tDataType;

/**
 * @brief Struct representing any data and it's type
 */
typedef struct {
    tDataValue value;
    tDataType dataType;
} tData;

/**
 * @brief Creates new global table
 */
void initGlobalSymTable();

/**
 * @brief Start of creating new function, or it's declaration
 * @param name
 */
void addFunction(char *name);

/**
 * @brief Add new parameter into stack of function's parameters
 * @param name
 */
void addParam(char *name);

#endif //IFJ_PROJECT_SEMANTIC_H
