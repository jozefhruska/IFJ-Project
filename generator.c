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

tDLList *instructionStack = NULL;
ContextPtr localContext, globalContext, expressionContext;

char *createSymbol(int count, ...) {
	va_list valist;
	char *result = NULL;
	size_t size = 0;

	va_start(valist, count);
	for (int i = 0; i < count; i++) size += sizeof(va_arg(valist, char *));
	va_end(valist);

	result = malloc(size);

	va_start(valist, count);
	strcpy(result, va_arg(valist, char *));
	for (int i = 1; i < count; i++) strcat(result, va_arg(valist, char *));
	va_end(valist);

	return result;
}

SymbolWrapperPtr createSymbolWrapper(char *symbol1, char *symbol2, char *symbol3, int size) {
	SymbolWrapperPtr wrapper;

	if ((wrapper = malloc(sizeof(struct sSymbolWrapper))) != NULL) {
		wrapper->symbol1 = symbol1;
		wrapper->symbol2 = symbol2;
		wrapper->symbol3 = symbol3;
		wrapper->size = size;

		return wrapper;
	} else {
		error_fatal(ERROR_INTERNAL);
		return NULL;
	}
}

void createInstruction(InstructionType type, SymbolWrapperPtr symbols) {
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

		case INSTR_IFJ: return ".IFJcode18";

		/* Debugging instructions */
		case INSTR_BREAK: return "BREAK";
		case INSTR_DPRINT: return "DPRINT";
	}
}

void freeInstruction(InstructionPtr instruction) {
	if (instruction->symbols != NULL) {
		if (instruction->symbols->symbol1 != NULL) free(instruction->symbols->symbol1);
		if (instruction->symbols->symbol2 != NULL) free(instruction->symbols->symbol2);
		if (instruction->symbols->symbol3 != NULL) free(instruction->symbols->symbol3);
	}

	free(instruction->symbols);
	free(instruction);
}

bool resolveInstruction() {
	tDLElemPtr firstElem = DLPopFirst(instructionStack);
	InstructionPtr instruction = (InstructionPtr) firstElem->data;

	if (instruction->symbols != NULL) {
		switch (instruction->symbols->size) {
			case 1:
				printf("%s %s\n", getInstructionHandle(instruction->type), instruction->symbols->symbol1);
				break;
			case 2:
				printf("%s %s %s\n", getInstructionHandle(instruction->type), instruction->symbols->symbol1, instruction->symbols->symbol2);
				break;
			case 3:
				printf("%s %s %s %s\n", getInstructionHandle(instruction->type), instruction->symbols->symbol1, instruction->symbols->symbol2, instruction->symbols->symbol3);
				break;
			default:
				error_fatal(ERROR_INTERNAL);
		}
	} else printf("%s\n", getInstructionHandle(instruction->type));

	freeInstruction(instruction);
	free(firstElem);
	return true;
}

void resolveAllInstructions() {
	while(instructionStack->First != NULL) resolveInstruction();
}

// static .IFJcode18 and first instruction
void _Init() {
	if (globalContext == NULL) {
		if ((globalContext = malloc(sizeof(struct sContext))) != NULL) {
			globalContext->key = NULL;
			globalContext->count = 0;
		} else error_fatal(ERROR_INTERNAL);
	} else {
		globalContext->key = NULL;
		globalContext->count = 0;
	}

	if (expressionContext == NULL) {
		if ((expressionContext = malloc(sizeof(struct sContext))) != NULL) {
			expressionContext->key = NULL;
			expressionContext->count = 0;
		} else error_fatal(ERROR_INTERNAL);
	} else {
		expressionContext->key = NULL;
		expressionContext->count = 0;
	}

	createInstruction(
		INSTR_IFJ,
		NULL
	);

	createInstruction(
		INSTR_JUMP,
		createSymbolWrapper(
			createSymbol(1, "$$main"),
			NULL,
			NULL,
			1
		)
	);
}

void _Function_start(char *id_name) {
	if (localContext == NULL) {
		if ((localContext = malloc(sizeof(struct sContext))) != NULL) {
			localContext->key = id_name;
			localContext->count = 0;
		} else error_fatal(ERROR_INTERNAL);
	} else {
		localContext->key = id_name;
		localContext->count = 0;
	}

	createInstruction(
		INSTR_JUMP,
		createSymbolWrapper(
			createSymbol(3, "$", id_name, "$end"),
			NULL,
			NULL,
			1
		)
	);

	createInstruction(
		INSTR_LABEL,
		createSymbolWrapper(
			createSymbol(2, "$", id_name),
			NULL,
			NULL,
			1
		)
	);

	createInstruction(
		INSTR_PUSHFRAME,
		NULL
	);

	createInstruction(
		INSTR_DEFVAR,
		createSymbolWrapper(
			createSymbol(4, "LF", "@", "%", "retval"),
			NULL,
			NULL,
			1
		)
	);

	createInstruction(
		INSTR_MOVE,
		createSymbolWrapper(
			createSymbol(4, "LF", "@", "%", "retval"),
			createSymbol(3, "nil", "@", "nil"),
			NULL,
			2
		)
	);
}

void _Function_param(char *id_name) {
	localContext->count++;

	char localParam[10];
	sprintf(localParam, "%d", localContext->count);

	createInstruction(
		INSTR_DEFVAR,
		createSymbolWrapper(
			createSymbol(3, "LF", "@", id_name),
			NULL,
			NULL,
			1
		)
	);

	createInstruction(
		INSTR_MOVE,
		createSymbolWrapper(
			createSymbol(3, "LF", "@", id_name),
			createSymbol(6, "LF", "@", "%", localContext->key, "$", localParam),
			NULL,
			2
		)
	);
}

void _Function_end(sToken *token) {
	char *type = "nil";
	char *value = "nil";

	if (token != NULL) {
		if (token->type == T_ID) {
			type = "LF";
		} else if (token->type == T_INT) {
			type = "int";
		} else if (token->type == T_DOUBLE) {
			type = "float";
		} else if (token->type == T_STRING) {
			type = "string";
		} else error_fatal(ERROR_INTERNAL);

		value = (char *)token->data;
	}

	createInstruction(
		INSTR_MOVE,
		createSymbolWrapper(
			createSymbol(4, "LF", "@", "%", "retval"),
			createSymbol(3, type, "@", value),
			NULL,
			2
		)
	);

	createInstruction(
		INSTR_POPFRAME,
		NULL
	);

	createInstruction(
		INSTR_RETURN,
		NULL
	);
}

void _Function_call_start(char *id_name) {
	if (localContext == NULL) {
		if ((localContext = malloc(sizeof(struct sContext))) != NULL) {
			localContext->key = id_name;
			localContext->count = 0;
		} else error_fatal(ERROR_INTERNAL);
	} else {
		localContext->key = id_name;
		localContext->count = 0;
	}

	createInstruction(
		INSTR_CREATEFRAME,
		NULL
	);
}

void _Function_call_param(sToken *token) {
	localContext->count++;

	char localParam[10];
	sprintf(localParam, "%d", localContext->count);

	char *type = "nil";
	char *value = "nil";

	if (token != NULL) {
		if (token->type == T_ID) {
			type = "LF";
		} else if (token->type == T_INT) {
			type = "int";
		} else if (token->type == T_DOUBLE) {
			type = "float";
		} else if (token->type == T_STRING) {
			type = "string";
		} else error_fatal(ERROR_INTERNAL);

		value = (char *)token->data;
	}

	createInstruction(
		INSTR_DEFVAR,
		createSymbolWrapper(
			createSymbol(6, "TF", "@", "%", localContext->key, "$", localParam),
			NULL,
			NULL,
			1
		)
	);

	createInstruction(
		INSTR_MOVE,
		createSymbolWrapper(
			createSymbol(6, "TF", "@", "%", localContext->key, "$", localParam),
			createSymbol(3, type, "@", value),
			NULL,
			2
		)
	);
}

void _Expression_assign(sToken *token) {
	char *data = (char *) token->data;
	int type = token->type;

	if (type == T_ID) {
		if ((expressionContext->key = malloc(sizeof(data))) != NULL) {
			expressionContext->key = data;
		} else error_fatal(ERROR_INTERNAL);
	} else error_fatal(ERROR_INTERNAL);

	createInstruction(
		INSTR_DEFVAR,
		createSymbolWrapper(
			createSymbol(3, "LF", "@", data),
			NULL,
			NULL,
			1
		)
	);
}

void _Expression(sToken *token) {
	char *data = (char *) token->data;
	int type = token->type;

	/* Assign expression result */
	if (token == NULL) {
		if (expressionContext->key != NULL) {
			createInstruction(
				INSTR_POPS,
				createSymbolWrapper(
					createSymbol(3, "LF", "@", expressionContext->key),
					NULL,
					NULL,
					1
				)
			);
		}

		expressionContext->key = NULL;
		expressionContext->count = 0;
	}

	switch (type) {
		case T_ID:
			createInstruction(
				INSTR_PUSHS,
				createSymbolWrapper(
					createSymbol(3, "LF", "@", data),
					NULL,
					NULL,
					1
				)
			);
			break;
		case T_INT:
			createInstruction(
				INSTR_PUSHS,
				createSymbolWrapper(
					createSymbol(3, "int", "@", data),
					NULL,
					NULL,
					1
				)
			);
			break;
		case T_DOUBLE:
			createInstruction(
				INSTR_PUSHS,
				createSymbolWrapper(
					createSymbol(3, "float", "@", data),
					NULL,
					NULL,
					1
				)
			);
			break;
		case T_STRING:
			createInstruction(
				INSTR_PUSHS,
				createSymbolWrapper(
					createSymbol(3, "string", "@", data),
					NULL,
					NULL,
					1
				)
			);
			break;
		case T_OPERATOR:
			expressionContext->count++;
			char localParam[10];
			sprintf(localParam, "%d", expressionContext->count);

			createInstruction(
				INSTR_DEFVAR,
				createSymbolWrapper(
					createSymbol(6, "LF", "@", "%", expressionContext->key, "$", localParam),
					NULL,
					NULL,
					1
				)
			);

			/* TODO: Type check */
			if (!strcmp("+", data)) { // Operator - Addition
				createInstruction(
					INSTR_ADDS,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", localParam),
						NULL,
						NULL,
						1
					)
				);
			} else if (!strcmp("-", data)) { // Operator - Subtraction
				createInstruction(
					INSTR_SUBS,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", localParam),
						NULL,
						NULL,
						1
					)
				);
			} else if (!strcmp("*", data)) { // Operator - Multiplication
				createInstruction(
					INSTR_MULS,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", localParam),
						NULL,
						NULL,
						1
					)
				);
			} else if (!strcmp("/", data)) { // Operator - Division
				createInstruction(
					INSTR_DIVS,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", localParam),
						NULL,
						NULL,
						1
					)
				);
			} else if (!strcmp("==", data)) { // Operator - Equal
				createInstruction(
					INSTR_EQS,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", localParam),
						NULL,
						NULL,
						1
					)
				);
			} else if (!strcmp("!=", data)) { // Operator - Not equal
				createInstruction(
					INSTR_EQS,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", localParam),
						NULL,
						NULL,
						1
					)
				);

				createInstruction(
					INSTR_NOT,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", localParam),
						NULL,
						NULL,
						1
					)
				);
			} else if (!strcmp(">", data)) { // Operator - Greater than
				createInstruction(
					INSTR_GTS,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", localParam),
						NULL,
						NULL,
						1
					)
				);
			} else if (!strcmp("<", data)) { // Operator - Lesser than
				createInstruction(
					INSTR_LTS,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", localParam),
						NULL,
						NULL,
						1
					)
				);
			} else if (!strcmp(">=", data)) { // Operator -- Greater or equal than
				expressionContext->count++;
				char tempParam1[10];
				sprintf(tempParam1, "%d", expressionContext->count);

				expressionContext->count++;
				char tempParam2[10];
				sprintf(tempParam2, "%d", expressionContext->count);

				createInstruction(
					INSTR_DEFVAR,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", tempParam1),
						NULL,
						NULL,
						1
					)
				);

				createInstruction(
					INSTR_DEFVAR,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", tempParam2),
						NULL,
						NULL,
						1
					)
				);

				createInstruction(
					INSTR_GTS,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", tempParam1),
						NULL,
						NULL,
						1
					)
				);

				createInstruction(
					INSTR_EQS,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", tempParam2),
						NULL,
						NULL,
						1
					)
				);

				createInstruction(
					INSTR_OR,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", localParam),
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", tempParam1),
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", tempParam2),
						3
					)
				);
			} else if (!strcmp("<=", data)) { // Operator -- Lesser or equal than
				expressionContext->count++;
				char tempParam1[10];
				sprintf(tempParam1, "%d", expressionContext->count);

				expressionContext->count++;
				char tempParam2[10];
				sprintf(tempParam2, "%d", expressionContext->count);

				createInstruction(
					INSTR_DEFVAR,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", tempParam1),
						NULL,
						NULL,
						1
					)
				);

				createInstruction(
					INSTR_DEFVAR,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", tempParam2),
						NULL,
						NULL,
						1
					)
				);

				createInstruction(
					INSTR_LTS,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", tempParam1),
						NULL,
						NULL,
						1
					)
				);

				createInstruction(
					INSTR_EQS,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", tempParam2),
						NULL,
						NULL,
						1
					)
				);

				createInstruction(
					INSTR_OR,
					createSymbolWrapper(
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", localParam),
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", tempParam1),
						createSymbol(6, "LF", "@", "%", expressionContext->key, "$", tempParam2),
						3
					)
				);
			}

			createInstruction(
				INSTR_PUSHS,
				createSymbolWrapper(
					createSymbol(6, "LF", "@", "%", expressionContext->key, "$", localParam),
					NULL,
					NULL,
					1
				)
			);
			break;
		default:
			break;
	}
}
