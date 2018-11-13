#include <stdio.h>
#include <string.h>
#include "_pseudoScanner.h"

int _i = 0;

sToken *_tokenBuffer = NULL;

sToken tokens[] = {
    /* TEST FUNCTION */
    { .data = "def",    .id = FUNC_DEFINE },
    { .data = "funkce", .id = ID },
    { .data = "(",      .id = L_BRACKET },
    { .data = "test",   .id = ID },
    { .data = "test",   .id = COMMA },
    { .data = "test",   .id = ID },
    { .data = "test",   .id = COMMA },
    { .data = "test",   .id = ID },
    { .data = "test",   .id = COMMA },
    { .data = "test",   .id = ID },
    { .data = "test",   .id = COMMA },
    { .data = "test",   .id = ID },
    { .data = "test",   .id = COMMA },
    { .data = "test",   .id = ID },
    { .data = ")",      .id = R_BRACKET },
    { .data = "",       .id = EOL },
    { .data = "end",    .id = FUNC_END },

    /* TEST STATEMENT */
    { .data = "if",     .id = IF_KEYWORD},
    { .data = "then",   .id = THEN_KEYWORD}, // TADY TO BUDE GENEROVAT BUS ERROR, DOKUD NEBUDE FUNKČNÍ <EXPR>
    { .data = "",       .id = EOL },
    { .data = "else",   .id = ELSE_KEYWORD},
    { .data = "",       .id = EOL },
    { .data = "end",    .id = END_KEYWORD},
    { .data = "",       .id = EOF },
};

sToken *getNextToken(){
    if(_tokenBuffer != NULL){
        sToken *tmp = _tokenBuffer;
        _tokenBuffer = NULL;
        return tmp;
    } else {
        return &(tokens[_i++]);
    }
}

void storeToken(sToken *storedToken){
    _tokenBuffer = storedToken;
}
