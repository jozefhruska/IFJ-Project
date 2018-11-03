// lexical analysator
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "str.h"
#include "scaner.h"

static char *keywords[KEYWORDS_LENGTH] = {"def", "do", "else", "end", "if", "not", "nil", "then", "while"};

static char operator[OPERATOR_LENGTH] = {'+', '-', '*', '<', '>', '=', '!'}; // single operator
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
bool isOperator(char input) {
	for (int i = 0; i<OPERATORS_LENGTH; i++) {
		if (strcmp(input, operator[i]) == 0) {
			return true;
		}
	}
	return false;
}

// variable to save input file
FILE *source;

void setSourceFile(FILE *f)
{
  source = f;
}

int getNextToken(string *attr)
// main function of lexical analysator
{
  Tstate state = INIT;
  char c;

	// clear attr
  strClear(attr);
  while (1)
  {     
  	// read next char
  	c = getc(source);
           
    switch (state)
    {
    	case INIT:

      	// white space
        if (isspace(c) && c != '\0')
	    		state = INIT;

				// identifier or keyword
				else if (c == '_' || islower(c))
				{
					strAddChar(attr, c);
					state = ID;
				}

				// not classified number
				else if (isdigit(c)) {
					strAddChar(attr, c);
					state = NUMBER;
				}
					
				else if (c == '{') return T_DELIMITER;
				else if (c == '}') return T_DELIMITER;
				else if (c == ';') 
				{
					strAddChar(attr, c);
					return T_COMMA;
				}
				else if (c == EOF) return T_EOF;
				else
				return T_ERR;

      break;
	 

      // ----- identifier -----
			case ID:
      	// komentar
        if (isalnum(c) || c == '_') 
				{
					strAddChar(attr, c);
				}

				else if (c == '?' || c == '!')
				{
					strAddChar(attr, c);
					state = ID_FUNC;
				}
				
        else
				{
					ungetc(c, source);
					if (isKeyword(attr->str))
					{
						return T_KEYWORD;
					}
					else return T_ID;
				}
      break;


			// ----- identifier that is function -----
			case ID_FUNC:
				// 
				if (isspace(c) || c == '(' || c == ')')
				{
					ungetc(c, source);
					return T_ID_FUNC;
				}
				// char after ? or ! is illegal
				else
				{
					ungetc(c, source);
					return T_ERR;
				}
			break;

			// ----- identifier that is function -----
			case NUMBER:
				// 
				if (isdigit(c))
				{
					strAddChar(attr, c);
				}
				// char after ? or ! is illegal
				else if (c == '.')
				{
					ungetc(c, source);
					state = DOUBLE;
				}
				else if (c == 'e' || c == 'E') 
				{
					ungetc(c, source);
					state = DOUBLE;
				}
				else if (!isdigit(c) || !isOperator(c) || c != ';') // TODO UPLNE NAPICU HOSI, ALE JAKOZE FEST
				{
					ungetc(c, source);
					return T_ERR;
				}
				else
				{
					ungetc(c, source);
					return T_INT;
				}
			break;
       
    }
  }
}
