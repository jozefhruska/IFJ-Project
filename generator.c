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

#include "generator.h"

SymbolPtr createSymbol(SymbolType type, SymbolLocation location, char *key, void *value) {
	SymbolPtr symbol;

	if ((symbol = malloc(sizeof(struct sSymbol))) != NULL) {
		if (type) {
			symbol->type = type;
		}
		if (location) {
			symbol->location = location;
		}
		if (key) {
			symbol->key = key;
		}
		if (value) {
			symbol->value = value;
		}

		//return concateSymbol(symbol); // GETTING READY FOR STRING CONVERSION (example -> "int@42")
		return symbol;
	} else {
		error_fatal(ERROR_INTERNAL);
		return NULL;
	}
}

// concatenate into one string variables/constants and their values
char *concateSymbol(SymbolPtr symbol) {

	// labels
	if (symbol->type == ST_LABEL) {
		if (symbol->value != NULL) {
			return stringConcate("", symbol->value, "$");
		}
	}

	// variables
	char *location;

	if (symbol->location == SL_GF) {
		location = "GF";
	} else if (symbol->location == SL_LF) {
		location = "LF";
	} else if (symbol->location == SL_TF) {
		location = "TF";
	}
	// constants
	else {
		char *type;

		if (symbol->type == ST_INTEGER) {
			type = "int";
		} else if (symbol->type == ST_FLOAT) {
			type = "float";
		} else if (symbol->type == ST_STRING) {
			type = "string";
		} else {
			error_fatal(ERROR_INTERNAL);
			return NULL;
		}

		if (symbol->value != NULL) {
			return stringConcate(type, (char *)symbol->value, "@");
		} else {
			error_fatal(ERROR_INTERNAL);
			return NULL;
		}
	}

	if (symbol->key != NULL) {
		return stringConcate(location, (char *)symbol->key, "@");
	} else {
		error_fatal(ERROR_INTERNAL);
		return NULL;
	}
}

void createInstruction(tDLList *instructionStack, InstructionType type, SymbolWrapperPtr symbols[3]) {
	/* Initialize stack at first attempt to create an instruction */
	if (instructionStack == NULL) {
		if ((instructionStack = malloc(sizeof(tDLList))) != NULL) DLInitList(instructionStack);
		else error_fatal(ERROR_INTERNAL);
	}

	InstructionPtr instruction;
	if ((instruction = malloc(sizeof(struct sInstruction))) != NULL) {
		instruction->type = type;
		instruction->symbols = symbols;

		DLInsertLast(instructionStack, (void *) instruction);
	} else error_fatal(ERROR_INTERNAL);
}

char *getInstructionHandle(InstructionType type) {
	switch (type) {

		/* Frame manipulation & function call instructions */
		case INSTR_MOVE: return "MOVE";
		case INSTR_CREATEFRAME: return "CREATEFRAME";
		case INSTR_PUSHFRAME: return "PUSHFRAME";
		case INSTR_POPFRAME: return "POPFRAME";
		case INSTR_DEFVAR: return "DEFVAR";
		case INSTR_CALL: return "CALL";
		case INSTR_RETURN: return "RETURN";

		case INSTR_PUSHS: return "PUSHS";
		case INSTR_POPS: return "POPS";
		case INSTR_CLEARS: return "CLEARS";

		/* Arithmetic instructions */
		case INSTR_ADD: return "ADD";
		case INSTR_SUB: return "SUB";
		case INSTR_MUL: return "MUL";
		case INSTR_DIV: return "DIV";
		case INSTR_IDIV: return "IDIV";

		case INSTR_ADDS: return "ADDS";
		case INSTR_SUBS: return "SUBS";
		case INSTR_MULS: return "MULS";
		case INSTR_DIVS: return "DIVS";
		case INSTR_IDIVS: return "IDIVS";

		/* Comparation(boolean) instructions */
		case INSTR_LT: return "LT";
		case INSTR_GT: return "GT";
		case INSTR_EQ: return "EQ";

		case INSTR_LTS: return "LTS";
		case INSTR_GTS: return "GTS";
		case INSTR_EQS: return "EQS";

		case INSTR_AND: return "AND";
		case INSTR_OR: return "OR";
		case INSTR_NOT: return "NOT";

		case INSTR_ANDS: return "ANDS";
		case INSTR_ORS: return "ORS";
		case INSTR_NOTS: return "NOTS";

		/* Conversion instructions */
		case INSTR_INT2FLOAT: return "INT2FLOAT";
		case INSTR_FLOAT2INT: return "FLOAT2INT";
		case INSTR_INT2CHAR: return "INT2CHAR";
		case INSTR_STRI2INT: return "STRI2INT";

		case INSTR_INT2FLOATS: return "INT2FLOATS";
		case INSTR_FLOAT2INTS: return "FLOAT2INTS";
		case INSTR_INT2CHARS: return "INT2CHARS";
		case INSTR_STRI2INTS: return "STRI2INNTS";

		/* I&O instructions */
		case INSTR_READ: return "READ";
		case INSTR_WRITE: return "WRITE";

		/* String instructions */
		case INSTR_CONCAT: return "CONCAT";
		case INSTR_STRLEN: return "STRLEN";
		case INSTR_GETCHAR: return "GETCHAR";
		case INSTR_SETCHAR: return "SETCHAR";

		/* Type instruction */
		case INSTR_TYPE: return "TYPE";

		/* Program flow instructions */
		case INSTR_LABEL: return "LABEL";
		case INSTR_JUMP: return "JUMP";
		case INSTR_JUMPIFEQ: return "JUMPIFEQ";
		case INSTR_JUMPIFNEQ: return "JUMPIFNEQ";
		case INSTR_JUMPIFEQS: return "JUMPIFEQS";
		case INSTR_JUMPIFNEQS: return "JUMPIFNEQS";
		case INSTR_EXIT: return "EXIT";

		/* Debugging instructions */
		case INSTR_BREAK: return "BREAK";
		case INSTR_DPRINT: return "DPRINT";
	}
}

bool resolveInstruction(tDLList *instructionStack) {
	tDLElemPtr firstElem = DLPopFirst(instructionStack);
	InstructionPtr instruction = (InstructionPtr) firstElem->data;

	switch (instruction->symbols->size) {
		case 0:
			printf("%s\n", getInstructionHandle(instruction->type));
			break;
		case 1:
			printf("%s %s\n", getInstructionHandle(instruction->type), concateSymbol(instruction->symbols->symbol1));
			break;
		case 2:
			printf("%s %s %s\n", getInstructionHandle(instruction->type), concateSymbol(instruction->symbols->symbol1), concateSymbol(instruction->symbols->symbol2));
			break;
		case 3:
			printf("%s %s %s %s\n", getInstructionHandle(instruction->type), concateSymbol(instruction->symbols->symbol1), concateSymbol(instruction->symbols->symbol2), concateSymbol(instruction->symbols->symbol3));
			break;
		default:
			error_fatal(ERROR_INTERNAL);
	}

	free(firstElem);
	return true;
}

/*
 * Built-in functions
*/

void generateInputs(tDLList *instructionStack) {
	addInstruction(instructionStack, "");
	// "\n# Built-in function INPUTS"
	// "\nLABEL $inputs"
	// "\nPUSHFRAME"
	// "\nDEFVAR LF@retval"
	// "\nMOVE LF@retval string@"
	// "\n"
}

void generateInputi(tDLList *instructionStack) {
	addInstruction(instructionStack, "");
	// \n# Built-in function INPUTI
	// \nLABEL $inputs
	// \nPUSHFRAME
	// \nDEFVAR LF@retval
	// \nMOVE LF@retval int@
	// \n
}

void generateInputf(tDLList *instructionStack) {
	addInstruction(instructionStack, "");
	// \n# Built-in function INPUTF
	// \nLABEL $inputs
	// \nPUSHFRAME
	// \nDEFVAR LF@retval
	// \nMOVE LF@retval floats@
	// \n
}

void generatePrint(tDLList *instructionStack) {

}

void generateLength(tDLList *instructionStack) {
	addInstruction(instructionStack, "");
	// \n# Built-in function LENGTH
	// \nLABEL $inputs
	// \nPUSHFRAME
	// \nDEFVAR LF@retval
	// \nMOVE LF@retval string@
	// \n

}

void generateSubstr(tDLList *instructionStack) {
	addInstruction(instructionStack, "");
	// \n# Built-in function SUBSTR
	// \nLABEL $inputs
	// \nPUSHFRAME
	// \nDEFVAR LF@retval
	// \nMOVE LF@retval string@
	// \n

}

void generateOrd(tDLList *instructionStack) {
	addInstruction(instructionStack, "");
	// \n# Built-in function ORD
	// \nLABEL $inputs
	// \nPUSHFRAME
	// \nDEFVAR LF@retval
	// \nMOVE LF@retval string@
	// \n

}

void generateChr(tDLList *instructionStack) {
	addInstruction(instructionStack, "");
	// \n# Built-in function CHR
	// \nLABEL $inputs
	// \nPUSHFRAME
	// \nDEFVAR LF@retval
	// \nMOVE LF@retval string@
	// \n

}

/*
 * Preparing functions
*/
void generateInit(tDLList *instructionStack) {
	addInstruction(instructionStack, "");
	// \n.IFJcode18
	// \n\nJUMP &&main

}

void generateMain(tDLList *instructionStack) {
	addInstruction(instructionStack, "");
	// \nLABEL &&main
	// \nCREATEFRAME
	// \nPUSHFRAME

}

void generateFunctionStart(tDLList *instructionStack) {
	addInstruction(instructionStack, "");
	// \nLABEL && FUNCNAME
	// \nCREATEFRAME
	// \nPUSHFRAME

}

void generateFunctionEnd(tDLList *instructionStack) {
	addInstruction(instructionStack, "");
	// \nPOPFRAME
	// \nRETURN

}
