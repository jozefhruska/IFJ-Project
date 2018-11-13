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

#ifndef IFJ_PROJECT_TAC_H
#define IFJ_PROJECT_TAC_H

/**
 * Types of instruction in three-address code
 */
typedef enum {
    ItAdd, // addition +
    ItSub, // substraction -
    ItEquals, // =
} tInstrType;

/**
 * Structure for one instruction in three-address code
 */
typedef struct {
    tInstrType instrType; // instruction type
    void *op1; // operand 1
    void *op2; // operand 2
    void *dest; // destination
} tInstr;

/**
 * Structure representing one item of the list of instructions
 */
typedef struct instrListItem{
    tInstr instr; // instruction
    struct instrListItem *next; // pointer to the next item
} tInstrListItem;

/**
 * Structure for a list of instructions
 */
typedef struct {
    struct instrListItem *first; // the first item of the list
    struct instrListItem *last; // the last item of the list
} tInstrList;

/**
 * Creates new instruction and adds it to instruction list
 *
 * @param type Type of instruction, +-= etc.
 * @param op1 First operand pointer
 * @param op2 Second operand pointer
 * @param dest Result destination pointer
 */
void generateInstruction(tInstrType type, void *op1, void *op2, void *dest);

#endif //IFJ_PROJECT_TAC_H
