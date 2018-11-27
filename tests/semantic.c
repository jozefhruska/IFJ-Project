/*
 *
 * Tests for semantic analysis
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <string.h>

#include "../semantic.h"

#define TEST(expr) \
assert(expr); \
printf(".");

#define TEST_FALSE(expr) \
assert(expr == false); \
printf(".");

#define TEST_NULL(expr) \
assert(expr == NULL); \
printf(".");

#define TEST_ERROR(expr) \
printf("\n\t[Error expected]"); \
printf("\n\t"); \
fflush(stdout); \
expr;

/*
 *
 *
 *
 *
 * In error_handler.c can't be exit function called in order to the tests were able to work!!!
 *
 *
 *
 *
 */

int main() {
    char *builtInFunctions[] = {"inputi", "inputs", "inputf", "print", "length", "substr", "ord", "chr"};


    // init global symbol table
    initGlobalSymTable();
    TEST(globalSymTable != NULL);

    // test all built-in functions are declared and defined
    for (int i = 0; i < 8; i++) {
        TEST(isFunctionDeclared(builtInFunctions[i]));
        TEST(isFunctionDefined(builtInFunctions[i]));
    }

    TEST(eachFunctionDefined());

    // test parameters of inputs, no params
    TEST_NULL(getNthParam("inputi", 0));
    TEST_NULL(getNthParam("inputi", 100));
    TEST_NULL(getNthParam("inputi", -1));
    TEST_NULL(getNthParam("inputi", 2));

    TEST_FALSE(isParamDeclared("inputi", "s"));
    TEST_FALSE(isParamDeclared("inputi", "inputi"));

    // new function
    addFunction("mojeFunkce");
    TEST_FALSE(isParamDeclared("mojeFunkce", "s"));
    addParam("s", true);
    TEST(isParamDeclared("mojeFunkce", "s"));
    TEST_ERROR(addFunction("mojeFunkce"));
    endFunction();

    TEST_FALSE(isFunctionDefined("mojeFunkce"));
    TEST(isFunctionDeclared("mojeFunkce"));

    TEST_ERROR(addParam("v", true)); // out of function, can't add parameter
    functionDefinition("mojeFunkce");
    TEST(isFunctionDefined("mojeFunkce"));
    TEST(isFunctionDeclared("mojeFunkce"));

    TEST(eachFunctionDefined());
    TEST(eachFunctionInTreeDefined(globalSymTable->root));

    // another function witout parameters
    addFunction("funkceDva");
    TEST_FALSE(isParamDeclared("funkceDva", "s"));
    TEST_FALSE(isFunctionDefined("funkceDva"));
    TEST(isFunctionDeclared("funkceDva"));
    TEST_FALSE(isParamDeclared("funkceDva", ""));
    TEST_NULL(getNthParam("funkceDva", 0));
    TEST_NULL(getNthParam("funkceDva", 1));
    addParam("priVar", true);
    TEST(strcmp(getNthParam("funkceDva", 0), "priVar") == 0);
    TEST(isParamDeclared("funkceDva", "priVar"));
    TEST_FALSE(isParamDeclared("funkceDva", "priVar "));

    // global variables, still in a function, can't add
    TEST_FALSE(isVarDeclared("mamRadVut"));
    TEST_ERROR(addVar("mamRadVut")); // can't add global variable inside a function
    TEST_FALSE(isVarDeclared("mamRadVut"));
    TEST_FALSE(isVarDeclared("mamRadMuni"));

    // get out of the function
    endFunction();
    addVar("mamRadVut");
    TEST(isVarDeclared("mamRadVut"));
    TEST_FALSE(isVarDeclared("mamRadMuni"));


    printf("\nThe end\n");
}
