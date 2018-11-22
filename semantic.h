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

/*
 *
 * Symbol table
 *
 */

/**
 * @brief Creates new global table
 */
void initGlobalSymTable();

/*
 *
 * Functions
 *
 */

/**
 * @brief Start of creating new function, or it's declaration
 * @param name
 */
void addFunction(char *name);

/**
 * @brief Add new parameter into list of function's parameters.
 * Can be used for creating new private variables too.
 * @pre First call addFunction()
 * @param name
 */
void addParam(char *name);

/**
 * @brief Sets the function defined to true
 * @param name Name of the function
 */
void functionDefinition(char *name);

/**
 * @brief End of function declaration or definition. After this next addFunction() can be called again.
 * @pre First call addFunction()
 */
void endFunction();

/**
 * @brief Returns true, if the function has been defined via functionDefinition(), returns false otherwise.
 * @param name Name of the function
 * @pre Function must be declared via addFunction()
 * @return bool Function defined
 */
bool isFunctionDefined(char *name);

/**
 * @brief Returns true, if the fuction has been declared via addFunction(), returns false otherwise
 * @param name Name of the function
 * @return bool Declared
 */
bool isFunctionDeclared(char *name);

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
* @return Pointer to BTVatiableData or NULL if not found.
*/
BTVariableData *getParam(char *functionName, char *paramName);

/**
* @brief Returns nth parameter of the function. Can return a private variable instead of parameter.
* @param functionName Name of the function.
* @param n Index of the parameter, starts with 0.
* @return Pointer to BTVariableData or NULL if not found.
*/
BTVariableData *getNthParam(char *functionName, unsigned int n);

/**
 * @brief Check, if each function in symbol table has been defined.
 * @return true if each function defined, else false
 */
bool eachFunctionDefined();

/*
 *
 * Global variables
 *
 */

/**
* @brief Create new global variable.
* @param name
*/
void addVar(char *name);

/**
 * @brief Returns true, if the global variable is declared, false otherwise.
 * @param name Name of the variable
 * @return bool
 */
bool isVarDeclared(char *name);

#endif //IFJ_PROJECT_SEMANTIC_H
