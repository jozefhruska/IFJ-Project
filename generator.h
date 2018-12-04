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

#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

#include "list.h"
#include "token.h"
#include "error_handler.h"
#include "scanner.h"
#include "generator_str.h"

typedef enum {
	/* Frame manipulation & function call instructions */
	INSTR_MOVE,
	INSTR_CREATEFRAME,
	INSTR_PUSHFRAME,
	INSTR_POPFRAME,
	INSTR_DEFVAR,
	INSTR_CALL,
	INSTR_RETURN,

	INSTR_PUSHS,
	INSTR_POPS,
	INSTR_CLEARS,

	/* Arithmetic instructions */
	INSTR_ADD,
	INSTR_SUB,
	INSTR_MUL,
	INSTR_DIV,
	INSTR_IDIV,

	INSTR_ADDS,
	INSTR_SUBS,
	INSTR_MULS,
	INSTR_DIVS,
	INSTR_IDIVS,

	/* Comparation(boolean) instructions */
	INSTR_LT,
	INSTR_GT,
	INSTR_EQ,

	INSTR_LTS,
	INSTR_GTS,
	INSTR_EQS,

	INSTR_AND,
	INSTR_OR,
	INSTR_NOT,

	INSTR_ANDS,
	INSTR_ORS,
	INSTR_NOTS,

	/* Conversion instructions */
	INSTR_INT2FLOAT,
	INSTR_FLOAT2INT,
	INSTR_INT2CHAR,
	INSTR_STRI2INT,

	INSTR_INT2FLOATS,
	INSTR_FLOAT2INTS,
	INSTR_INT2CHARS,
	INSTR_STRI2INTS,

	/* I&O instructions */
	INSTR_READ,
	INSTR_WRITE,

	/* String instructions */
	INSTR_CONCAT,
	INSTR_STRLEN,
	INSTR_GETCHAR,
	INSTR_SETCHAR,

	/* Type instruction */
	INSTR_TYPE,

	/* Program flow instructions */
	INSTR_LABEL,
	INSTR_JUMP,
	INSTR_JUMPIFEQ,
	INSTR_JUMPIFNEQ,
	INSTR_JUMPIFEQS,
	INSTR_JUMPIFNEQS,
	INSTR_EXIT,

	/* Starting print .IFJcode18 */
	INSTR_IFJ,

	/* Debugging instructions */
	INSTR_BREAK,
	INSTR_DPRINT
} InstructionType;

typedef struct sSymbolWrapper {
	char *symbol1;
	char *symbol2;
	char *symbol3;
	int size;
} *SymbolWrapperPtr;

typedef struct sInstruction {
	InstructionType type;
	SymbolWrapperPtr symbols;
} *InstructionPtr;

typedef struct sLocalContext {
	char *key;
	int count;
} *LocalContextPtr;

char *createSymbol(int count, ...);
void createInstruction(InstructionType type, SymbolWrapperPtr symbols);
bool resolveInstruction();
void resolveAllInstructions();

void _Init();
void _Function_start(char *id_name);
void _Function_param(char *id_name);
void _Function_end(sToken *token);
void _Function_call_start(char *id_name);
void _Function_call_param(sToken *token);

#endif
