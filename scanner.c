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

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"

static char *keywords[KEYWORDS_LENGTH] = {"def", "do", "else", "end", "if", "not", "nil", "then", "while"};
static char delimiter[DELIMITER_LENGTH] = {'(', ')', ','};
static char operator[OPERATOR_LENGTH] = {'+', '-', '*', '<', '>', '=', '!'};					   // single operator
static char *operators[OPERATORS_LENGTH] = {"+", "-", "*", "=", "<", ">", "<=", ">=", "==", "!="}; // final operator
// static char escape[ESCAPE_LENGTH] = {'\"', '\n', '\t', '\s', '\\'};

/*================= DML EDIT ==================*/

sToken *storedToken = NULL;

void store_token(sToken *token)
{
	storedToken = token;
}

/*================= END OFDML EDIT ==================*/

// check if loaded char is delimiter
bool isDelimiter(char input)
{
	for (int i = 0; i < DELIMITER_LENGTH; i++)
	{
		if (input == delimiter[i])
		{
			return true;
		}
	}
	return false;
}

// check if loaded char is operator
bool isOperator(char input)
{
	for (int i = 0; i < OPERATOR_LENGTH; i++)
	{
		if (input == operator[i])
		{
			return true;
		}
	}
	return false;
}

// check if loaded string is from keywords
bool isFromKeywords(char *input)
{
	for (int i = 0; i < KEYWORDS_LENGTH; i++)
	{
		if (strcmp(input, keywords[i]) == 0)
		{
			return true;
		}
	}
	return false;
}

// check if loaded string is from operators
bool isFromOperators(char *input)
{
	for (int i = 0; i < OPERATORS_LENGTH; i++)
	{
		if (strcmp(input, operators[i]) == 0)
		{
			return true;
		}
	}
	return false;
}

// char isFromEscape(char *input) {
// 	for (int i = 0; i<ESCAPE_LENGTH; i++) {
// 		if (strcmp(input, escape[i]) == 0) {
// 			return escape[i];
// 		}
// 	}
// 	return NULL;
// }

// variable to save input file
FILE *source;

void setSourceFile(FILE *f)
{
	source = f;
}

sToken *getNextToken()
// main function of lexical analysator
{
	/*================= DML EDIT ==================*/
	if(storedToken != NULL){
		sToken *tmp = storedToken;
		storedToken = NULL;
		return tmp;
	}
	/*================= END OFDML EDIT ==================*/

	Tstate state = INIT;
	char c;
	char buff;

	string output;
	string stack;
	strInit(&stack);
	strInit(&output);

	sToken *token;
	token = (sToken *)malloc(sizeof(struct Token));

	tokenClear(token);

	while ((c = fgetc(source)))
	{

		switch (state)
		{
		// ---------------------------------------- INIT CASE ----------------------------------------
		case INIT:

			// white space
			if (isspace(c) && c != '\n')
			{
				state = INIT;
			}

			else if (c == EOF)
			{
				tokenChangeType(token, T_EOF);
				return token;
			}

			// end of line
			else if (c == '\n')
			{
				strAddChar(&output, c);
				tokenChangeBoth(token, &output, T_EOL);
				return token;
			}

			// identifier or keyword
			else if (c == '_' || islower(c))
			{
				strAddChar(&output, c);
				state = ID;
			}

			// not classified number
			else if (isdigit(c))
			{
				strAddChar(&output, c);
				state = NUMBER;
			}

			else if (c == '"')
			{
				state = STRING;
			}

			// operator
			else if (isOperator(c))
			{
				strAddChar(&output, c);
				state = OPERATOR;
			}

			//delimiter '('
            else if (c == '(')
            {
                strAddChar(&output, c);
                tokenChangeBoth(token, &output, T_LEFT_BRACKET);
                return token;
            }
            //delimiter ')'
            else if (c == ')')
            {
                strAddChar(&output, c);
                tokenChangeBoth(token, &output, T_RIGHT_BRACKET);
                return token;
            }
            //delimiter ','
            else if (c == ',')
            {
                strAddChar(&output, c);
                tokenChangeBoth(token, &output, T_COMMA);
                return token;
            }

			// error handling
			else
			{
				tokenChangeType(token, T_ERR);
				return token;
			}

			break;

		// ---------------------------------------- ID CASE ----------------------------------------
		case ID:
			// komentar
			if (isalnum(c) || c == '_')
			{
				strAddChar(&output, c);
				state = ID;
			}

			// special kind of id that can be only function
			else if (c == '?' || c == '!')
			{
				strAddChar(&output, c);
				state = ID_FUNC;
			}

			// handle possibility to be keyword
			else
			{
				ungetc(c, source);
				if (isFromKeywords(output.str))
				{
					tokenChangeBoth(token, &output, T_KEYWORD);
					return token;
				}
				else
				{
					tokenChangeBoth(token, &output, T_ID);
					return token;
				}
			}
			break;

		// ---------------------------------------- ID_FUNC CASE ----------------------------------------
		case ID_FUNC:
			//
			if (isspace(c) || c == '(' || c == EOF)
			{
				ungetc(c, source);
				tokenChangeBoth(token, &output, T_ID_FUNC);
				return token;
			}
			// char after ? or ! is illegal
			else
			{
				ungetc(c, source);
				tokenChangeType(token, T_ERR);
				return token;
			}
			break;

		// ---------------------------------------- NUMBER CASE ----------------------------------------
		case NUMBER:
			//
			if (isdigit(c))
			{
				strAddChar(&output, c);
				state = NUMBER;
			}
			// char after ? or ! is illegal
			else if (c == '.')
			{
				buff = fgetc(source);
				if (!isdigit(buff))
				{
					tokenChangeType(token, T_ERR);
					return token;
				}
				ungetc(buff, source);
				ungetc(c, source);
				state = DOUBLE;
			}
			else if (c == 'e' || c == 'E')
			{
				ungetc(c, source);
				state = DOUBLE;
			}
			else
			{
				ungetc(c, source);
				tokenChangeBoth(token, &output, T_INT);
				return token;
			}
			break;

		// ---------------------------------------- DOUBLE CASE ----------------------------------------
		case DOUBLE:
			if (c == '.')
			{
				strAddChar(&output, c);
				state = DOUBLE_DOT;
			}
			else if (c == 'e' || c == 'E')
			{
				strAddChar(&output, c);
				c = fgetc(source);
				if (c == '+' || c == '-')
				{
					strAddChar(&output, c);
				}
				else
				{
					ungetc(c, source);
				}
				state = DOUBLE_EXP;
			}
			break;

		// ---------------------------------------- DOUBLE_DOT CASE ----------------------------------------
		case DOUBLE_DOT:
			if (isdigit(c))
			{
				strAddChar(&output, c);
				state = DOUBLE_DOT;
			}
			else if (c == 'e' || c == 'E')
			{
				strAddChar(&output, c);
				buff = fgetc(source);

				if (buff == '+' || buff == '-' || isdigit(buff))
				{
					strAddChar(&output, buff);
					state = DOUBLE_EXP;
				}
				else
				{
					tokenChangeType(token, T_ERR);
					return token;
				}
			}
			else
			{
				tokenChangeBoth(token, &output, T_DOUBLE);
				return token;
			}
			break;

		// ---------------------------------------- DOUBLE_EXP CASE ----------------------------------------
		case DOUBLE_EXP:
			if (isdigit(c))
			{
				strAddChar(&output, c);
				state = DOUBLE_EXP;
			}
			else
			{
				if (isspace(c) || c == EOF)
				{
					tokenChangeBoth(token, &output, T_DOUBLE);
				}
				else if (isOperator(c))
				{
					tokenChangeBoth(token, &output, T_DOUBLE);
				}
				else
				{
					tokenChangeType(token, T_ERR);
				}
				ungetc(c, source);
				return token;
			}
			break;

		// ---------------------------------------- STRING CASE ----------------------------------------
		case STRING:
			if (c == '"') // SPATNE
			{
				// if (output.str != NULL)
				// {
				// 	tokenChangeBoth(&token, &output, T_STRING);
				// }
				// else
				// {
				// 	tokenChangeType(&token, T_STRING);
				// }
				// return token;
			}
			// else if (c == '\\')
			// {
			// 	buff = fgetc(source);
			// 	if (buff == '"' || buff == 'n' || buff == 't' || buff == 's' || buff == '\\')
			// 	{
			// 		char *temp;
			// 		strAddChar(&stack, c);
			// 		strAddChar(&stack, buff);
			// 		if (temp = isFromEscape(&temp))
			// 		{

			// 		}
			// 	}
			// }
			// else if (c > 31)
			// {
			// 	strAddChar(&output, c);
			// 	state = STRING;
			// }
			break;

		// ---------------------------------------- OPERATOR CASE ----------------------------------------
		case OPERATOR:
			if (isOperator(c))
			{
				strAddChar(&output, c);
				if (isFromOperators(output.str))
				{
					tokenChangeBoth(token, &output, T_OPERATOR);
					return token;
				}
				state = OPERATOR;
			}

			else
			{
				ungetc(c, source);

				if (isFromOperators(output.str))
				{
					tokenChangeBoth(token, &output, T_OPERATOR);
					return token;
				}
				else
				{
					tokenChangeType(token, T_ERR);
					return token;
				}
			}
			break;
		}
	}
	tokenChangeType(token, T_ERR);
	return token;
}
