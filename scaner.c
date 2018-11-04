// lexical analysator
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "str.h"
#include "scaner.h"

static char *keywords[KEYWORDS_LENGTH] = {"def", "do", "else", "end", "if", "not", "nil", "then", "while"};
static char delimiter[DELIMITER_LENGTH] = {'(', ')', ','};
static char operator[OPERATOR_LENGTH] = {'+', '-', '*', '<', '>', '=', '!'}; // single operator
static char *operators[OPERATORS_LENGTH] = {"+", "-", "*", "<", ">", "<=", ">=", "==", "!="}; // final operator

// check if loaded char is delimiter
bool isDelimiter(char input) {
	for (int i = 0; i<3; i++) {
		if (strcmp(input, delimiter[i]) == 0) {
			return true;
		}
	}
	return false;
}

// check if loaded char is operator
bool isOperator(char input) {
	for (int i = 0; i<OPERATORS_LENGTH; i++) {
		if (strcmp(input, operator[i]) == 0) {
			return true;
		}
	}
	return false;
}

// check if loaded string is from keywords
bool isFromKeywords(char *input) {
	for (int i = 0; i<KEYWORDS_LENGTH; i++) {
		if (strcmp(input, keywords[i]) == 0) {
			return true;
		}
	}
	return false;
}

// check if loaded string is from operators
bool isFromOperators(char *input) {
	for (int i = 0; i<KEYWORDS_LENGTH; i++) {
		if (strcmp(input, operators[i]) == 0) {
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

  printf("printf debug jak pica 2\n");

	// clear attr
  strClear(attr);
  while (c = getc(source))
  {     
  	// read next char
	if (c == EOF)
	{
		return T_EOF;
	}

	printf("char: %c\n", c);
           
    switch (state)
    {
    	// ---------------------------------------- INIT CASE ----------------------------------------
		case INIT:

			// white space
			if (isspace(c) && c != '\0')
			{
				state = INIT;
			}

			// end of line
			else if (c == '\0')
			{
				strAddChar(attr, c);
				return T_EOL;
			}

			// identifier or keyword
			else if (c == '_' || islower(c))
			{
				strAddChar(attr, c);
				state = ID;
			}

			// not classified number
			else if (isdigit(c)) 
			{
				strAddChar(attr, c);
				state = NUMBER;
			}

			// operator
			else if (isOperator(c))
			{
				strAddChar(attr, c);
				state = OPERATOR;
			}

			//delimiter
			else if (isDelimiter(c))
			{
				strAddChar(attr, c);
				return T_DELIMITER;
			}

			// error handling
			else
			{
				return T_ERR;
			}

      	break;

      	// ---------------------------------------- ID CASE ----------------------------------------
		case ID:
			// komentar
			if (isalnum(c) || c == '_') 
			{
				strAddChar(attr, c);
			}

			// special kind of id that can be only function
			else if (c == '?' || c == '!')
			{
				strAddChar(attr, c);
				state = ID_FUNC;
			}
			
			// handle possibility to be keyword
			else
			{
				ungetc(c, source);
				if (isFromKeywords(attr->str))
				{
					state = KEYWORD;
					return T_KEYWORD;
				}
				else return T_ID;
			}
      	break;

		// ---------------------------------------- ID_FUNC CASE ----------------------------------------
		case ID_FUNC:
			// 
			if (isspace(c) || c == '(')
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

		// ---------------------------------------- NUMBER CASE ----------------------------------------
		case NUMBER:
			// 
			if (isdigit(c))
			{
				strAddChar(attr, c);
				state = NUMBER;
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
			else if (!isdigit(c) || !isOperator(c)) // TODO UPLNE NAPICU HOSI, ALE JAKOZE FEST
			{
				ungetc(c, source);
				return T_ERR;
			}
			else
			{
				ungetc(c, source);
				state = INTEGER;
				return T_INT;
			}
		break;

		// ---------------------------------------- DOUBLE CASE ----------------------------------------
		case DOUBLE:

		break;

		// ---------------------------------------- STRING CASE ----------------------------------------
		case STRING:

		break;

		// ---------------------------------------- OPERATOR CASE ----------------------------------------
		case OPERATOR:
			if (isDelimiter(c))
			{
				strAddChar(attr, c);
				if (isFromOperators(attr->str)) 
				{
					strAddChar(attr, c);
					return T_OPERATOR;
				}
				state = OPERATOR;
			}

			else 
			{
				if (isFromOperators(attr->str))
				{
					ungetc(c, source);
					return T_OPERATOR;
				}
				else 
				{
					ungetc(c, source);
					return T_ERR;
				}
			}
		break;

    }
  }
}
