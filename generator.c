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

void createInstruction(tDLList *instructionStack, InstructionType type, SymbolPtr *symbols) {
	InstructionPtr instruction;
	if ((instruction = malloc(sizeof(struct sInstruction))) != NULL) {
		instruction->type = type;
		instruction->symbols = symbols;

		DLInsertLast(instructionStack, (void *) instruction);
	} else error_fatal(ERROR_INTERNAL);
}

bool resolveInstruction(tDLList *instructionStack) {
	tDLElemPtr firstElem = DLPopFirst(instructionStack);
	InstructionPtr instruction = (InstructionPtr) DLPopFirst(instructionStack)->data;



	free(firstElem);
	return false;
}
