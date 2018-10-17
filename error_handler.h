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

#ifndef ERROR_HANDLER_HEADER
#define ERROR_HANDLER_HEADER

#include <stdio.h>

/* Error codes table */
typedef enum errorCodes {
	ERROR_LEXICAL = 1,
	ERROR_SYNTACTIC = 2,
	ERROR_SEMANTIC_DEF = 3,
	ERROR_SEMANTIC_RUN = 4,
	ERROR_SEMANTIC_PARAM = 5,
	ERROR_SEMANTIC_OTHER = 6,
	ERROR_ZERO_DIVISION = 9,
	ERROR_INTERNAL = 99
} ERROR_CODES;

#endif ERROR_HANDLER_HEADER