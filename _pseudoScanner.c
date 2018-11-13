#include <stdio.h>
#include <string.h>
#include "_pseudoScanner.h"

int _i = 0;

sToken *_tokenBuffer = NULL;

sToken tokens[] = {
    { .data = "def",    .id = FUNC_DEFINE },
    { .data = "funkce", .id = ID },
    { .data = "(",      .id = L_BRACKET },
    { .data = ")",      .id = R_BRACKET },
    { .data = "",       .id = EOL },
    { .data = "end",    .id = FUNC_END },
    { .data = "",    .id = EOF },
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
