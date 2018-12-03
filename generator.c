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

	if (symbol->value != NULL) {
		return stringConcate(location, (char *)symbol->value, "@");
	} else {
		error_fatal(ERROR_INTERNAL);
		return NULL;
	}
}

void createInstruction(tDLList *instructionStack, InstructionType type, SymbolPtr symbols[3]) {
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

bool resolveInstruction(tDLList *instructionStack) {
	tDLElemPtr firstElem = DLPopFirst(instructionStack);
	InstructionPtr instruction = (InstructionPtr) firstElem->data;



	free(firstElem);
	return false;
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
