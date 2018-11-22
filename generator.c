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

		return symbol;
	} else {
		error_fatal(ERROR_INTERNAL);
		return NULL;
	}
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
		instruction->symbol[0] = symbols[0];
		instruction->symbol[1] = symbols[1];
		instruction->symbol[2] = symbols[2];

		DLInsertLast(InstructionStack, (void *) instruction);
	} else error_fatal(ERROR_INTERNAL);
}

resolveIntruction();