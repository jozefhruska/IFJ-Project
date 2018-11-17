#ifndef scanner__
#define scanner__

typedef struct __token{
    void *data;
    int id;
} sToken;

typedef enum {
    FUNC_DEFINE,
    FUNC_END,
    ID,
    L_BRACKET,
    R_BRACKET,
    EOL,
    COMMA,
    IF_KEYWORD,
    THEN_KEYWORD,
    ELSE_KEYWORD,
    END_KEYWORD
} tokenTypes;

sToken *getNextToken();
void storeToken(sToken*);

#endif
