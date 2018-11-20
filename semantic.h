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

#include <stdbool.h>
#include "symtable.h"

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

/**
 * @brief Create new variable,
 * @param name
 */
void addVar(char *name);

/**
 * @brief End of function declaration or definition
 * @pre First call addFunction()
 */
void endFunction();

/**
 * @brief Sets the function defined to true
 * @param name Name of the function
 */
void functionDefinition(char *name);

/**
 * @brief Returns true, if the function val defined via functionDefinition(), returns false otherwise.
 * @param name Name of the function
 * @return bool Function defined
 */
bool isFunctionDefined(char *name);

/**
 * @brief Returns true, if the global variable is declared, false otherwise.
 * @param name Name of the variable
 * @return bool
 */
bool isVarDeclared(char *name);

/**
 * @brief Returns true, if the function has a parameter with the name, false otherwise.
 * @param functionName Name of the function
 * @param paramName Name of the variable
 * @return bool
 */
bool isParamDeclared(char *functionName, char *paramName);

/**
 * @brief Returns pointer to the parameter with the name of the function
 * @param functionName Name of the functoin
 * @param paramName Name of the parameter
 * @return Pointer to BTVatiableData
 */
BTVariableData *getParam(char *functionName, char *paramName);

/**
 * @brief Returns true, if the fuction has been declared via addFunction(), returns false otherwise
 * @param name Name of the function
 * @return bool Declared
 */
bool isFunctionDeclared(char *name);

/**
 * @brief Returns the global variable, if found, null otherwise.
 * @param name Name of the global variable
 * @return
 */
BTVariableData* getVar(char *name);

#endif //IFJ_PROJECT_SEMANTIC_H
