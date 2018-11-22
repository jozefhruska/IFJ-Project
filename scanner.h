#ifndef __scanner
#define __scanner
//hlavicka pro lexikalni analyzator
#include "token.h"
#include "list.h"
#include <stdio.h>
#include "list.h"

//lengths
#define KEYWORDS_LENGTH 9
#define DELIMITER_LENGTH 3
#define OPERATOR_LENGTH 7
#define OPERATORS_LENGTH 10
#define ESCAPE_LENGTH 5

//klicova slova
#define SETZERO 10
#define READ    11
#define WRITE   12
#define WHILE   13

//operatory inkrementace a dekrementace
#define INC     20
#define DEC     21

//jednotlive znaky
#define LEFT_VINCULUM  30 // '{'
#define RIGHT_VINCULUM 31 // '}'
#define SEMICOLON      32 // ';'

//specialni znaky
#define END_OF_FILE    40

//chybove hlasky
#define LEX_ERROR    -1

//type of state
typedef enum {
    INIT,
    ID,
    ID_FUNC,
    STRING,
    STRING_ESCAPE,
    STRING_HEXA,
    NUMBER,
    DOUBLE,
    DOUBLE_EXP,
    DOUBLE_DOT,
    OPERATOR,
    LINE_COMMENT
} Tstate;

//type of token
typedef enum {
    //scanner end and error handling
    T_EOF,
    T_ERR,
    //data types
    T_ID,
    T_ID_FUNC,
    T_INT,
    T_DOUBLE,
    T_STRING,
    //keywords
    T_KEYWORD,
    //operators
    T_OPERATOR,
    //delimiters
    T_DELIMITER,
    T_LEFT_BRACKET,
    T_RIGHT_BRACKET,
    T_COMMA,
    T_EOL

} Ttoken;

typedef struct _buffer_element {
    struct _buffer_element *next;
    sToken *data;
} TokenBufferElement;

typedef struct _buffer {
    TokenBufferElement *first_element;
} TokenBuffer;

//hlavicka funkce simulujici lexikalni analyzator

bool isDelimiter(char input);
bool isOperator(char input);
bool isFromKeywords(char *input);
bool isFromOperators(char *input);

int hexadecimalToDecimal(string *hexValue);
char *itoa(int i, char b[]);

void setSourceFile(FILE *f);

sToken *getNextToken();
void store_token(sToken *token);

void BufferInit(TokenBuffer**);
void BufferPush(TokenBuffer*, sToken*);
sToken *BufferPop(TokenBuffer*);

void StorePrevious(sToken*);

#endif
