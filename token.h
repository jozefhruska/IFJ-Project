#ifndef __token
#define __token
#include <stdbool.h>

typedef struct
{
  char* str;		// misto pro dany retezec ukonceny znakem '\0'
  int length;		// skutecna delka retezce
  int allocSize;	// velikost alokovane pameti
} string;

typedef struct Token {
    int type;
    void *data;
} sToken;

void tokenClear(sToken *t);
bool tokenChangeData(sToken *t, string *s);
bool tokenChangeType(sToken *t, int state);
bool tokenChangeBoth(sToken *t, string *s, int state);

int strInit(string *s);
void strFree(string *s);

void strClear(string *s);
int strAddChar(string *s1, char c);
#endif
