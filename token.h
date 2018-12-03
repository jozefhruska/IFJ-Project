#ifndef __token
#define __token

#include <stdbool.h>

/**
 * @brief  Structure representing an array of chars and is self-named "string".
 */
typedef struct
{
  char* str;		// space for string with ending char '\0'
  int length;		// real length of string
  int allocSize;	// size of allocated memory
} string;

/**
 * @brief  Structure representing a single token with type and data.
 */
typedef struct Token {
    int type;
    void *data;
} sToken;

/**
 * @brief  Clear content of token (data and type).
 * @note   Function does not include free().
 * @param  *t: sToken with data and type
 * @retval None
 */
void tokenClear(sToken *t);

/**
 * @brief  Fill token only with data.
 * @note   Overwrites old data of token.
 * @param  *t: sToken
 * @param  *s: string with data
 * @retval Boolean if operation was done successfully.
 */
bool tokenChangeData(sToken *t, string *s);

/**
 * @brief  Fill token only with type.
 * @note   Overwrites old type of token.
 * @param  *t: sToken
 * @param  state: int type of token from enum
 * @retval Boolean if operation was done successfully.
 */
bool tokenChangeType(sToken *t, int state);

/**
 * @brief  Fill token with both data and type.
 * @note   Overwrites old data and type of token.
 * @param  *t: sToken
 * @param  *s: string with data
 * @param  state: int type of token from enum
 * @retval Boolean if operation was done successfully.
 */
bool tokenChangeBoth(sToken *t, string *s, int state);

/**
 * @brief  Initialize new string with NULL value.
 * @param  *s: new string
 * @retval 0 for SUCCESS/ 1 for ERROR.
 */
int strInit(string *s);

/**
 * @brief  Unalloc memory of string.
 * @param  *s: string
 * @retval 0 for SUCCESS/ 1 for ERROR.
 */
void strFree(string *s);

/**
 * @brief  Clear value of str and length in string.
 * @note   Do not reallocate.
 * @param  *s: string
 * @retval 0 for SUCCESS/ 1 for ERROR.
 */
void strClear(string *s);

/**
 * @brief  Attach to end of string new char.
 * @note   do not overwrite last char '\0'.
 * @param  *s: string
 * @param  c: single char
 * @retval 0 for SUCCESS/ 1 for ERROR.
 */
int strAddChar(string *s1, char c);

#endif
