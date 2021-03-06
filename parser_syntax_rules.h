#ifndef PARSER_SYNTAX_RULES
#define PARSER_SYNTAX_RULES

int parametersRemaining; // number of params that are remaining for function call
char *currentFunctionName; // name of current function

int parser_parse_prog();
int parser_parse_func();

/**
 * @param declaration TRUE if in function declaration, FALSE if in function call
 * @param declared TRUE if the function is called and was declared before the call
 */
int parser_parse_params(bool declaration, bool declared);

/**
 * @param declaration TRUE if in function declaration, FALSE if in function call
 * @param declared TRUE if the function is called and was declared before the call
 */
int parser_parse_params_next(bool declaration, bool declared);
int parser_parse_body();
int parser_parse_cond();
int parser_parse_cond_else_block();
int parser_parse_loop();
int parser_parse_assign();

/**
 * @param declared TRUE if the function is called and was declared before the call
 */
int parser_parse_func_call(bool declared);

#endif
