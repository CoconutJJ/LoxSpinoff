#ifndef TOKEN_H
#define TOKEN_H
#include "../types.h"

/**
 * Log error and line to stderr and exit.
 */
void raise(char *error, int line);

/**
 * Copy n bytes from src to dest and append a null terminator at the end.
 * Returns the number of bytes copied from src.
 */
int nstrcp(char *dest, char *src, int str_len);

/**
 *  Adds a token to the linked list. Pass NULL for value if no value is needed.
 *
 */
void add_token(LITERAL t, char *value);
/**
 *  Peek at the token after current
 */
char peek(char *code, int *current);

/**
 *  If the characters after current match with c, advance the current up to the
 *  last matching character
 *
 *  Returns 1 if valid match, 0 otherwise
 */
int matchChar(char *code, int *current, char *c);

/**
 * Returns 1 if c is a character from A-Z case insensitive.
 */
int isAlpha(char c);

/**
 *  Returns 1 if c is chracter from 0-9
 */
int isNum(char c);

/**
 * Tokenize a string.
 */
int string(char *code, int *current);

/**
 *  Tokenize a number
 */
int number(char *code, int *current);

/**
 *  Returns the keyword literal if identifier is a keyword. Returns -1 otherwise
 */
LITERAL matchIdentifier(char *identifier);

/**
 *  Parse the identifier.
 */
int identifier(char *code, int *current);

/**
 * Tokenize the code.
 */
TOKEN* tokenize(char *code);
#endif