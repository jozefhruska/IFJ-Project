#ifndef __scanner
#define __scanner

#include "token.h"
#include "list.h"
#include <stdio.h>

/**
 * @brief  Lengths of arrays.
 */
#define KEYWORDS_LENGTH 8
#define DELIMITER_LENGTH 3
#define OPERATOR_LENGTH 8
#define OPERATORS_LENGTH 11
#define ESCAPE_LENGTH 5

/**
 * @brief  Enumaration of possibilities in final state automaton.
 */
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
    BLOCK_COMMENT,
    LINE_COMMENT
} Tstate;

/**
 * @brief  Enumeration of token types.
 */
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
    T_EOL,
    T_SPACE

} Ttoken;

/**
 * @brief  Structure representing a single element in buffer.
 */
typedef struct _buffer_element {
    struct _buffer_element *next;
    sToken *data;
} TokenBufferElement;

/**
 * @brief  Structure representing a whole buffer.
 */
typedef struct _buffer {
    TokenBufferElement *first_element;
} TokenBuffer;

/**
 * @brief  Search function for delimiter.
 * @param  input: single char
 * @retval Boolean if char matches with char from array.
 */
bool isDelimiter(char input);

/**
 * @brief  Search function for operator.
 * @param  input: single char
 * @retval Boolean if char matches with char from array.
 */
bool isOperator(char input);

/**
 * @brief  Search function for operator.
 * @param  *input: string with potentional operator
 * @retval Boolean if string matches with string from array.
 */
bool isFromOperators(char *input);

/**
 * @brief  Search function for keyword.
 * @param  *input: string with potentional keyword
 * @retval Boolean if string matches with string from array.
 */
bool isFromKeywords(char *input);

/**
 * @brief  Convert hexadecimal number to decimal number.
 * @note   Input number is in string form.
 * @param  *hexValue: string with number
 * @retval Decimal number.
 */
int hexadecimalToDecimal(string *hexValue);

/**
 * @brief  Initialise file with source code.
 * @param  *f: type of FILE
 * @retval None
 */
void setSourceFile(FILE *f);

/**
 * @brief  Main function of scanner to submit next token from source file.
 * @note   Function is made via deterministic finite automaton.
 * @retval Token with both data and type
 */
sToken *getNextToken();

/**
 * @brief  Function that uses parser to temporary store unused tokens.
 * @param  *token: type of sToken
 * @retval None
 */
void store_token(sToken *token);

/**
 * @brief  Initializes a token buffer.
 * @note   Sets initial node to NULL.
 * @param  TokenBuffer**: Initial buffer
 * @retval None
 */
void BufferInit(TokenBuffer**);

/**
 * @brief  Push token to last position in Buffer.
 * @param  TokenBuffer*: Buffer with tokens
 * @param  sToken*: Token to store in buffer
 * @retval None
 */
void BufferPush(TokenBuffer*, sToken*);

/**
 * @brief  Copy and delete first token from buffer.
 * @param  TokenBuffer*: Buffer with tokens
 * @retval Token with data and type
 */
sToken *BufferPop(TokenBuffer*);

/**
 * @brief  Function to help scanner identify previous token.
 * @note   Copy last token to variable previous.
 * @param  sToken*: Last token with data and type
 * @retval None
 */
void StorePrevious(sToken*);

#endif
