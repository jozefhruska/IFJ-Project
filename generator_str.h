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

#ifndef GENERATOR_STR_HEADER
#define GENERATOR_STR_HEADER

#include <string.h>
#include "list.h"
#include "error_handler.h"

/*
 * @brief  Concatenate two strings with possible between string.
 * @param  s1: First string
 * @param  s2: Second string
 * @param  between: String to include in between of s1 & s2
 * @retval Array of chars.
*/
char *stringConcate(char *s1, char *s2, char *between);

#endif
