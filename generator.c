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
		symbol->type = type;
		symbol->location = location;
		symbol->key = key;
		symbol->value = value;

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

void generateInit() {
	fprintf(stdout, ".IFJcode18\nJUMP &&main\n"); // TODO neprintovat, pushnout do stacku
}

void generateMain() {
	fprintf(stdout, "LABEL &&main\nCREATEFRAME\nPUSHFRAME\n"); // TODO neprintovat, pushnout do stacku
}

void createInstruction(tDLList *InstructionStack, InstructionType type, SymbolPtr symbols[3]) {
	/* Initialize stack at first attempt to create an instruction */
	if (InstructionStack == NULL) {
		if ((InstructionStack = malloc(sizeof(tDLList))) != NULL) DLInitList(InstructionStack);
		else error_fatal(ERROR_INTERNAL);
	}

	InstructionPtr instruction;
	if ((instruction = malloc(sizeof(struct sInstruction))) != NULL) {
		instruction->type = type;
		instruction->symbols = symbols;

		DLInsertLast(InstructionStack, (void *) instruction);
	} else error_fatal(ERROR_INTERNAL);
}

bool resolveInstruction(tDLList *instructionStack) {
	tDLElemPtr firstElem = DLPopFirst(instructionStack);
	InstructionPtr instruction = (InstructionPtr) DLPopFirst(instructionStack)->data;



	free(firstElem);
	return false;
}
