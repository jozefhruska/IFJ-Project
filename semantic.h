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
#include "token.h"


BTNodePtr currentFunction; // item from the global symbol table, currently created function

/*
 *
 * Symbol table
 *
 */

STable *globalSymTable; // global symbol table

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
 * If the parameter is in the list, throws an error
 * @pre First call addFunction()
 * @param name Name of the parameter
 * @param isParam true if is a parameter, false if is a local variable
 */
void addParam(char *name, bool isParam);

/**
 * @brief Creates new function that must be defined in future.
 * This is used when a function, that isn't defined yet is called.
 * @param name Name of the function
 */
void addFuncionDefinedLater(char *name);

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
 * @brief Returns true, if the function has a parameter or local variable with the name, false otherwise.
 * @param functionName Name of the function
 * @param paramName Name of the variable
 * @pre The function must be declared via addFunction()
 * @return bool
 */
bool isParamDeclared(char *functionName, char *paramName);

/**
 * @brief Returns nth parameter of the function. Can return a private variable instead of parameter.
 * @param functionName Name of the function.
 * @param n Index of the parameter, starts with 0.
 * @pre The function must be declared via addFunction()
 * @return Pointer to BTVariableData or NULL if not found.
 */
char *getNthParam(char *functionName, unsigned int n);

/**
 * @brief Check, if each function in symbol table has been defined.
 * @return true if each function defined, else false
 */
bool eachFunctionDefined();

/**
 * @brief Checks if each function in the tree is defined - preorder
 * @param root Pointer to the root
 * @return true if each function in tree is defined, else otherwise
 */
bool eachFunctionInTreeDefined(BTNodePtr root);

/**
 * @brief Returns number of parameters, that the function has.
 * Parameters only, private variables are excluded.
 * @param functionName Name of the function
 * @return Parameters count of the function
 */
unsigned getParamCount(char *functionName);

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

/**
 * @brief Searchs for the string in the list, if finds, returns true and active is the found one. Otherwise returns false.
 * @param List
 * @param string Value of searched string
 * @return bool Found
 */
bool DLSearchParam(tDLList *List, char *string);

/**
 * @brief Does nothing if the variable is declared.
 * Variable must be global in global scope.
 * In a function it can be global or private.
 * @param token Token with id
 */
void isVariableVisibleOrError(const sToken *token);

/**
 * @brief Returns true if the function can have unlimited count of parameters, e.g. function print.
 * False otherwise.
 * @param functionName Name of the function
 * @return bool Unlimited parameters count
 */
bool isFunctionParamsUnlimited(char *functionName);

#endif //IFJ_PROJECT_SEMANTIC_H
