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

#include "list.h"

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

	/* Debugging instructions */
	INSTR_BREAK,
	INSTR_DPRINT
} InstructionType;

typedef enum {
	ST_INTEGER,
	ST_FLOAT,
	ST_STRING
} SymbolType;

typedef enum {
	SL_GF,
	SL_LF,
	SL_TF
} SymbolLocation;

typedef struct sSymbol {
	SymbolType type;
	char *key;
	void *value;
} *SymbolPtr;

typedef struct sInstruction {
	InstructionType type;
	SymbolPtr *symbol[3];
} *InstructionPtr;



void createInstruction(tDLList *InstructionStack, InstructionType type, SymbolPtr symbols[2]);

#endif