// lexikalni analyzator
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "str.h"
#include "scaner.h"

static char *keywords[KEYWORDS_LENGTH] = {"def", "do", "else", "end", "if", "not", "nil", "then", "while"};

static char operator[] = {'+', '-', '*', '<', '>', '=', '!'}; // single operator
static char *operators[OPERATORS_LENGTH] = {"+", "-", "*", "<", ">", "<=", ">=", "==", "!="}; // final operator

// check if loaded string is from keywords
bool isKeyword(char *input) {
	for (int i = 0; i<KEYWORDS_LENGTH; i++) {
		if (strcmp(input, keywords[i]) == 0) {
			return true;
		}
	}
	return false;
}

// check if loaded string is from operators
bool isOperator(char *input) {
	for (int i = 0; i<OPERATORS_LENGTH; i++) {
		if (strcmp(input, operators[i]) == 0) {
			return true;
		}
	}
	return false;
}

// promenna pro ulozeni vstupniho souboru
FILE *source;

void setSourceFile(FILE *f)
{
  source = f;
}

int getNextToken(string *attr)
// hlavni funkce lexikalniho analyzatoru
{
  Tstate state = INIT;
  int c;
	// vymazeme obsah atributu a v pripade identifikatoru
  // budeme postupne do nej vkladat jeho nazev
  strClear(attr);
  while (1)
  {     
  	// nacteni dalsiho znaku
  	c = getc(source);
           
    switch (state)
    {
    	case INIT:
      	// zakladni stav automatu 
        if (isspace(c))
        	// bila mista - ignorovat
	    		state = INIT;
				else if (c == '_' || islower(c))
				// identifikator nebo klicove slovo
				{
					strAddChar(attr, c);
					state = ID;
				}
				else if (isdigit(c))
					// not classified number
					state = NUMBER;
				else if (c == '-')
					// operator --
					state = 4;
				else if (c == '{') return LEFT_VINCULUM;
				else if (c == '}') return RIGHT_VINCULUM;
				else if (c == ';') return SEMICOLON;
				else if (c == EOF) return END_OF_FILE;
				else
				return LEX_ERROR;

      break;
	 

      case ID:
      	// komentar
        if (isalnum(c) || c == '_') 
				{
					strAddChar(attr, c);
					state = ID;
				}

				else if (c == '?' || c == '!')
				{
					strAddChar(attr, c);
					state = ID_FUNC;
				}
				
        else
        	ungetc(c, attr);
        	return T_ID;
      break;

			// ----- identifier that is function -----
			case ID_FUNC:
				// 
				if (isspace(c) || c == '(' || c == ')')
				{
					ungetc(c, attr);
					return T_ID_FUNC;
				}
				// char after ? or ! is illegal
				else
				{
					ungetc(c, attr);
					return T_ERR;
				}

			break;
       
    }
  }
}
