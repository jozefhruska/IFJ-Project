// Simple library to work with tokens and string

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "token.h"

#define LEN_INC 8

#define ERROR 1
#define SUCCESS 0

// --- TOKEN functions

// clear content of included token
void tokenClear(sToken *t)
{
    t->data = NULL;
    t->type = 0;
}

// only change data of token
bool tokenChangeData(sToken *t, string *s)
{
    t->data = s->str;
    return true;
}

// only change type of token
bool tokenChangeType(sToken *t, int state)
{
    t->type = state;
    return true;
}

// change both data and type of token
bool tokenChangeBoth(sToken *t, string *s, int state)
{
    t->data = s->str;
    t->type = state;
    return true;
}

// --- STRING functions

// function creates new string
int strInit(string *s)
{
   if ((s->str = (char*) malloc(LEN_INC)) == NULL)
      return ERROR;
   s->str[0] = '\0';
   s->length = 0;
   s->allocSize = LEN_INC;
   return SUCCESS;
}

// function frees string from cache
void strFree(string *s)
{
   free(s->str);
}

// function clears content of string
void strClear(string *s)
{
   s->str[0] = '\0';
   s->length = 0;
}

// attach to end of string one char
int strAddChar(string *s1, char c)
{
   if (s1->length + 1 >= s1->allocSize)
   {
      // pamet nestaci, je potreba provest realokaci
      if ((s1->str = (char*) realloc(s1->str, s1->length + LEN_INC)) == NULL)
         return ERROR;
      s1->allocSize = s1->length + LEN_INC;
   }
   s1->str[s1->length] = c;
   s1->length++;
   s1->str[s1->length] = '\0';
   return SUCCESS;
}
