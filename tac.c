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

/*
 * Three-address code generator
 */

#include <stdlib.h>

#include "tac.h"

tInstrList *instrList; // global instruction list - TODO: replace with the variable from parser.c

/**
 * Creates new instruction and adds it to instruction list
 *
 * @param type Type of instruction, +-= etc.
 * @param op1 First operand pointer
 * @param op2 Second operand pointer
 * @param dest Result destination pointer
 */
void generateInstruction(tInstrType type, void *op1, void *op2, void *dest)
{
    // create the instruction struct
    tInstr instruction;

    instruction.instrType = type;
    instruction.op1 = op1;
    instruction.op2 = op2;
    instruction.dest = dest;

    // create new list item
    tInstrListItem* created = malloc(sizeof(tInstrListItem));
    created->instr = instruction;
    created->next = null;

    // insert the instruction to the end of the list of instructions
    if (instrList->last == NULL) {
        // first instruction
        instrList->first = created;
        instrList->last = created;
    } else {
        // not first instruction
        instrList->last->next = created;
        instrList->last = created;
    }
}
