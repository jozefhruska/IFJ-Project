#ifndef scanner__
#define scanner__

typedef struct __token{
    char name[100];
    int id;
} sToken;

int getNextToken(char *);

#endif
