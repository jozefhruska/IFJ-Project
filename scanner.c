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

/*================= DML EDIT ==================*/

/*
TokenBuffer *stored_tokens = NULL;

void BufferInit(TokenBuffer **buffer){
	(*buffer)->first_element = NULL;
}

void BufferPush(TokenBuffer *buffer, sToken *token){
	if(buffer->first_element == NULL){
		TokenBufferElement *newElement = (TokenBufferElement*)malloc(sizeof(TokenBufferElement));
		newElement->next = NULL;
		newElement->data = token;
		buffer->first_element = newElement;	
	} else {
		TokenBufferElement *endOfBuffer = buffer->first_element;
		while(endOfBuffer->next != NULL) endOfBuffer = endOfBuffer->next;
		TokenBufferElement *newElement = (TokenBufferElement*)malloc(sizeof(TokenBufferElement));
		newElement->next = NULL;
		newElement->data = token;
		endOfBuffer->next = newElement;
	}
}

sToken *BufferPop(TokenBuffer *buffer){
	TokenBufferElement *elem = buffer->first_element;
	buffer->first_element = elem->next;
	sToken *retValue = elem->data;
	free(elem);
	return retValue;
}

void store_token(sToken *token){
	if(stored_tokens == NULL){
		stored_tokens = malloc(sizeof(TokenBuffer));
		BufferInit(&stored_tokens);
		BufferPush(stored_tokens, token);
	} else {
		BufferPush(stored_tokens, token);
	}
}
*/

sToken *stored_token = NULL;

void store_token(sToken *token){
	stored_token = token;
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

// Function to convert hexadecimal to decimal 
int hexadecimalToDecimal(string *hexValue) 
{    
    int len = strlen(hexValue->str); 
      
    // Initializing base value to 1, i.e 16^0 
    int base = 1; 
      
    int dec_val = 0; 
      
    // Extracting characters as digits from last character 
    for (int i=len-1; i>=0; i--) 
    {    
        // if character lies in '0'-'9', converting  
        // it to integral 0-9 by subtracting 48 from 
        // ASCII value. 
        if (hexValue->str[i]>='0' && hexValue->str[i]<='9') 
        { 
            dec_val += (hexValue->str[i] - 48)*base; 
                  
            // incrementing base by power 
            base = base * 16; 
        } 
  
        // if character lies in 'A'-'F' , converting  
        // it to integral 10 - 15 by subtracting 55  
        // from ASCII value 
        else if (hexValue->str[i]>='A' && hexValue->str[i]<='F') 
        { 
            dec_val += (hexValue->str[i] - 55)*base; 
          
            // incrementing base by power 
            base = base*16; 
        } 
    } 
      
    return dec_val; 
}

// convert integer to string
char *itoa(int i, char *b)
{
    char const digit[] = "0123456789";
    char* p = b;

    if (i < 0)
	{
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do
	{ //Move to where representation ends
        ++p;
    	shifter = shifter/10;
    } while (shifter);
    *p = '\0';
    do
	{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    } while (i);

    return b;
}

// variable to save input file
FILE *source;

// variable to save previous token
sToken *previous = NULL;

void setSourceFile(FILE *f)
{
	source = f;
}

void StorePrevious(sToken *token){
	if(previous != NULL){
		//TODO: Uvolňovat paměť předchozího tokenu
	}
	previous = malloc(sizeof(sToken));
	*previous = *token;
}

sToken *getNextToken()
// main function of lexical analysator
{
	// if (previous)
	// {
	// 	printf("PREVIOUS token state: %d\n", previous->type);
	// }

	/*
	if(stored_tokens != NULL){
		if(stored_tokens->first_element != NULL){
			return BufferPop(stored_tokens);
		}
	}
	*/

	if(stored_token != NULL){
		sToken *retValue = stored_token;
		stored_token = NULL;
		return retValue;
	}

	sToken *token;
	token = (sToken *)malloc(sizeof(struct Token));

	/*================= DML EDIT ==================*/
	// void DLCopyLast(storedTokens, token);
	// // return token;
	// if (token != NULL)
	// {
	// 	printf("stored token: %s\n", (char *)token->data);
	// }
	

	// if(token != NULL){
	// 	void DLDeleteLast(storedTokens);
	// 	return token;
	// }
	/*================= END OFDML EDIT ==================*/

	Tstate state = INIT;
	char c;
	char buff;
	int count;
  	int integer;

	string output;
	string stack;
	strInit(&stack);
	strInit(&output);

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
				strAddChar(&stack, ' ');
				tokenChangeBoth(previous, &output, SPACE);
				state = INIT;
			}
			else if (c == EOF)
			{
				tokenChangeType(token, T_EOF);
				StorePrevious(token);
				return token;
			}
			// end of line
			else if (c == '\n')
			{
				strAddChar(&output, c);
				tokenChangeBoth(token, &output, T_EOL);
				StorePrevious(token);
				return token;
			}
			// line comment
			else if (c == '#')
			{
				state = LINE_COMMENT;
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
			// start of string
			else if (c == '"')
			{
				state = STRING;
			}
			// possible block comment
			else if (c == '=')
			{
				strAddChar(&stack, c);
				buff = fgetc(source);
				if (!islower(buff))
				{
					ungetc(buff, source);
					strClear(&stack);
					strAddChar(&output, c);
					state = OPERATOR;
				}
				else if (islower(buff))
				{
					count = 1;
					strAddChar(&stack, buff);
					while (islower(buff))
					{
						buff = fgetc(source);
						count++;
						if(islower(buff))
						{
							strAddChar(&stack, buff);
						}
					} 

					if (!strcmp(stack.str, "=begin"))
					{
						state = BLOCK_COMMENT;
					}
					else if (!strcmp(stack.str, "=end"))
					{
						tokenChangeType(token, T_ERR);
						return token;
					}
					else
					{
						for (int i = count; i>=1; i--)
						{
							ungetc(stack.str[i], source);
						}

						strClear(&stack);
						strAddChar(&output, '=');
						tokenChangeBoth(token, &output, T_OPERATOR);
						return token;
					}
				}
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
				StorePrevious(token);
				return token;
			}
			//delimiter ')'
			else if (c == ')')
			{
				strAddChar(&output, c);
				tokenChangeBoth(token, &output, T_RIGHT_BRACKET);
				StorePrevious(token);
				return token;
			}
			//delimiter ','
			else if (c == ',')
			{
				strAddChar(&output, c);
				tokenChangeBoth(token, &output, T_COMMA);
				StorePrevious(token);
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
					StorePrevious(token);
					return token;
				}
				else
				{
					tokenChangeBoth(token, &output, T_ID);
					StorePrevious(token);
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
				tokenChangeBoth(token, &output, T_ID);
				StorePrevious(token);
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
			else if (!isspace(c) && c != '\n' && c != EOF)
			{
				tokenChangeType(token, T_ERR);
				return token;
			}
			else
			{
				ungetc(c, source);
				tokenChangeBoth(token, &output, T_INT);
				token->data = strtol((char *)token->data, NULL, 10);
				StorePrevious(token);
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
				strAddChar(&output, 'e');
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
				// strAddChar(&output, c);
				strAddChar(&output, 'e'); // GETTING READY FOR CONVERSION TO DOUBLE
				buff = fgetc(source);
				
				if (buff == '+' || buff == '-')
				{
					strAddChar(&output, buff);
					buff = fgetc(source);
					if (!isdigit(buff))
					{
						tokenChangeType(token, T_ERR);
						return token;
					}
					strAddChar(&output, buff);
					state = DOUBLE_EXP;
				}
				else if (isdigit(buff))
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
				double convert;
				convert = strtod(output.str, NULL); // GETTING READY FOR CONVERSION TO DOUBLE
				token->data = (void *)&convert;
				StorePrevious(token);
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
					double convert;
					convert = strtod(output.str, NULL); // GETTING READY FOR CONVERSION TO DOUBLE
					token->data = (void *)&convert;
				}
				else if (isOperator(c))
				{
					tokenChangeBoth(token, &output, T_DOUBLE);
					double convert;
					convert = strtod(output.str, NULL); // GETTING READY FOR CONVERSION TO DOUBLE
					token->data = (void *)&convert;
				}
				else
				{
					tokenChangeType(token, T_ERR);
				}
				ungetc(c, source);
				StorePrevious(token);
				return token;
			}
		break;

		// ---------------------------------------- STRING CASE ----------------------------------------
		case STRING:
			if (c == '"') // end of string
			{
				tokenChangeBoth(token, &output, T_STRING);
				StorePrevious(token);
				return token;
			}
			else if (c == '\\') // escape sequence
			{
				state = STRING_ESCAPE;
			}
			else if (c != '\n')
			{
				strAddChar(&output, c);
			}
			else
			{
				tokenChangeType(token, T_ERR);
			}
		break;

		// ---------------------------------------- STRING_ESCAPE CASE ----------------------------------------
		case STRING_ESCAPE:

			state = STRING;

			if (c == 'x')
			{
				state = STRING_HEXA;
			}
			else if (c == '"')
			{
				strAddChar(&output, '"');

			}
			else if (c == 'n')
			{
				strAddChar(&output, '\n');
			}
			else if (c == 't')
			{
				strAddChar(&output, '\t');
			}
			else if (c == 's')
			{
				strAddChar(&output, ' ');
			}
			else if (c == '\\')
			{
				strAddChar(&output, '\\');
			}
			else
			{
				tokenChangeType(token, T_ERR);
				return token;
			}
			
		break;

		// ---------------------------------------- STRING_HEXA CASE ----------------------------------------
		case STRING_HEXA:

			state = STRING;
			
			count = 0;
			integer = 0;
			strClear(&stack);

			while (count <= 1)
			{
				if (isdigit(c))
				{
					strAddChar(&stack, c);
					count++;
					c = fgetc(source);
				}
				else if (c >= 65 && c <= 70)
				{
					strAddChar(&stack, c);
					count++;
					c = fgetc(source);
				}
				else
				{
					tokenChangeType(token, T_ERR);
					return token;
				}
			}

			ungetc(c, source);
			integer = hexadecimalToDecimal(&stack);
			strClear(&stack);
			strAddChar(&output, (char)integer);
		break;

		// ---------------------------------------- OPERATOR CASE ----------------------------------------
		case OPERATOR:
			if (isOperator(c))
			{
				strAddChar(&output, c);
				if (isFromOperators(output.str))
				{
					tokenChangeBoth(token, &output, T_OPERATOR);
					StorePrevious(token);
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
					//StorePrevious(token);
					return token;
				}
				else
				{
					tokenChangeType(token, T_ERR);
					return token;
				}
			}
		break;

		// ---------------------------------------- LINE_COMMENT CASE ----------------------------------------
		case LINE_COMMENT:
			if (c == '\n')
			{
				strAddChar(&output, c);
				tokenChangeBoth(token, &output, T_EOL);
				StorePrevious(token);
				return token;
			}
			else if (c == EOF)
			{
				tokenChangeType(token, T_EOF);
				StorePrevious(token);
				return token;
			}
		break;

		// ---------------------------------------- BLOCK_COMMENT CASE ----------------------------------------
		case BLOCK_COMMENT:
			if (c == '=')
			{
				strClear(&stack);
				strAddChar(&stack, c);
				buff = fgetc(source);
				if (!islower(buff))
				{
					state = BLOCK_COMMENT;
				}
				else if (islower(buff))
				{
					count = 1;
					strAddChar(&stack, buff);
					while (islower(buff))
					{
						buff = fgetc(source);
						count++;
						if(islower(buff))
						{
							strAddChar(&stack, buff);
						}
					} 

					if (!strcmp(stack.str, "=end"))
					{
						state = INIT;
					}
					else
					{
						state = BLOCK_COMMENT;
					}
				}
			}
			else if (c != '=' && c != EOF)
			{
				state = BLOCK_COMMENT;
			}
			else if (c == EOF)
			{
				tokenChangeType(token, T_EOF);
				previous = token;
				return token;
			}
		break;
		}
	}
	tokenChangeType(token, T_ERR);
	return token;
}
