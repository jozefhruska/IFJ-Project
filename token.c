//jednoducha knihovna pro praci s nekonecne dlouhymi retezci
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "token.h"

#define LEN_INC 8
// konstanta STR_LEN_INC udava, na kolik bytu provedeme pocatecni alokaci pameti
// pokud nacitame retezec znak po znaku, pamet se postupne bude alkokovat na
// nasobky tohoto cisla 

#define ERROR 1
#define SUCCESS 0

// --- TOKEN functions

void tokenClear(sToken *t)
{
    t->data = NULL;
    t->type = 0;
}

bool tokenChangeData(sToken *t, string *s)
{
    t->data = s->str;
    return true;
}

bool tokenChangeType(sToken *t, int state)
{
    t->type = state;
    return true;
}

bool tokenChangeBoth(sToken *t, string *s, int state)
{
    t->data = s->str;
    t->type = state;
    return true;
}

// --- STRING functions

int strInit(string *s)
// funkce vytvori novy retezec
{
   if ((s->str = (char*) malloc(LEN_INC)) == NULL)
      return ERROR;
   s->str[0] = '\0';
   s->length = 0;
   s->allocSize = LEN_INC;
   return SUCCESS;
}

void strFree(string *s)
// funkce uvolni retezec z pameti
{
   free(s->str);
}

void strClear(string *s)
// funkce vymaze obsah retezce
{
   s->str[0] = '\0';
   s->length = 0;
}

int strAddChar(string *s1, char c)
// prida na konec retezce jeden znak
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

int strCopyString(string *s1, string *s2)
// prekopiruje retezec s2 do s1
{
   int newLength = s2->length;
   if (newLength >= s1->allocSize)
   {
      // pamet nestaci, je potreba provest realokaci
      if ((s1->str = (char*) realloc(s1->str, newLength + 1)) == NULL)
         return ERROR;
      s1->allocSize = newLength + 1;
   }
   strcpy(s1->str, s2->str);
   s1->length = newLength;
   return SUCCESS;
}

int strCmpString(string *s1, string *s2)
// porovna oba retezce a vrati vysledek
{
   return strcmp(s1->str, s2->str);
}

int strCmpConstStr(string *s1, char* s2)
// porovna nas retezec s konstantnim retezcem
{
   return strcmp(s1->str, s2);
}

char *strGetStr(string *s)
// vrati textovou cast retezce
{
   return s->str;
}

int strGetLength(string *s)
// vrati delku daneho retezce
{
   return s->length;
}
