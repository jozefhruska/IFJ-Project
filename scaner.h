//hlavicka pro lexikalni analyzator

//lengths
#define KEYWORDS_LENGTH 9
#define DELIMITER_LENGTH 3
#define OPERATOR_LENGTH 7
#define OPERATORS_LENGTH 9

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
    KEYWORD,
    STRING,
    NUMBER,
    INTEGER,
    DOUBLE,
    OPERATOR,
    DELIMITER
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
    T_EOL

} Ttoken;

//hlavicka funkce simulujici lexikalni analyzator
void setSourceFile(FILE *f);
int getNextToken(string *attr);

// bool isDelimiter(char input);
// bool isOperator(char input);

// bool isFromKeywords(char *input);
// bool isFromOperators(char *input);
