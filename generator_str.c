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

#include "generator_str.h"

char *stringConcate(char *s1, char *s2, char *between) {
	
	int sizeOfBetween = 1;

	if (between != NULL){
		sizeOfBetween += strlen(between);
	}
	
	char *output = malloc(sizeof(char)*(strlen(s1)+strlen(s2)+sizeOfBetween));

	strcpy(output, s1);
	if (between != NULL){
		strcat(output, between);
	}
	strcat(output, s2);

	return output;
}