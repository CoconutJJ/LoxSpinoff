#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types.h"

/**
 *  Linked List of Tokens
 */
TOKEN *token_list = NULL;
TOKEN *token_end = NULL;

int line = 1;

/**
 * Log error and line to stderr and exit.
 */
void raise(char *error, int line)
{

    fprintf(stderr, "line %d: %s", line, error);
    exit(EXIT_FAILURE);
}

/**
 * Copy n bytes from src to dest and append a null terminator at the end.
 * Returns the number of bytes copied from src.
 */
int nstrcp(char *dest, char *src, int str_len)
{

    int init = str_len;
    while (str_len > 0)
    {

        if (!(*src))
            break;

        *dest = *src;
        dest++;
        src++;
        str_len--;
    }
    *dest = '\0';

    return init - str_len;
}

/**
 *  Adds a token to the linked list. Pass NULL for value if no value is needed.
 *
 */
void add_token(LITERAL t, char *value)
{

    TOKEN *new_token = malloc(sizeof(TOKEN) + (value ? strlen(value) + 1 : 0));

    new_token->t = t;
    new_token->next = NULL;
    new_token->line = line;
    if (value)
    {
        strcpy(new_token->value, value);
    }
    if (!token_list)
    {
        token_list = new_token;
        token_end = new_token;
    }
    else
    {

        token_end->next = new_token;
        token_end = new_token;
    }
}

/**
 *  Peek at the token after current
 */
char peek(char *code, int *current)
{

    return code[(*current) + 1];
}

/**
 *  If the characters after current match with c, advance the current up to the
 *  last matching character
 *
 *  Returns 1 if valid match, 0 otherwise
 */
int matchChar(char *code, int *current, char *c)
{
    int initial = *current;
    (*current)++;
    char *s = &(code[*current]);

    while (*c)
    {
        if (*c != *s)
        {
            *current = initial;
            return 0;
        }

        (*current)++;
        c++;
        s++;
    }

    (*current)--;
    return 1;
}

/**
 * Returns 1 if c is a character from A-Z case insensitive.
 */
int isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/**
 *  Returns 1 if c is chracter from 0-9
 */
int isNum(char c)
{
    return (c >= '0' && c <= '9');
}

/**
 * Tokenize a string.
 */
int string(char *code, int *current)
{
    int str_len = 0;
    while (peek(code, current) != '"')
    {
        if (code[*current] == '\\')
        {
            (*current)++;
        }
        str_len++;
        (*current)++;
    }

    char str[str_len + 1];

    nstrcp(str, &(code[*current]), str_len);

    add_token(STRING, str);

    (*current)++;

    return 1;
}
/**
 *  Tokenize a number
 */
int number(char *code, int *current)
{

    int decimal = 0;
    char c;

    char *start = &(code[*current]);
    char *end = start;

    while (1)
    {
        c = code[*current];
        if (!isNum(c))
        {

            if (c == '.' && decimal == 0)
            {
                decimal = 1;
            }
            else
            {
                break;
            }
        }
        (*current)++;
        end++;
    }

    end--;

    int len = end - start + 1;

    char num[len + 1];

    nstrcp(num, start, len);

    add_token(decimal ? FLOAT : INT, num);

    return 1;
}

/**
 *  Returns the keyword literal if identifier is a keyword. Returns -1 otherwise
 */
LITERAL matchIdentifier(char *identifier)
{

    if (strcmp(identifier, "if") == 0)
    {

        return IF;
    }

    if (strcmp(identifier, "else") == 0)
    {
        return ELSE;
    }

    if (strcmp(identifier, "while") == 0)
    {
        return WHILE;
    }

    if (strcmp(identifier, "for") == 0)
    {
        return FOR;
    }

    if (strcmp(identifier, "func") == 0)
    {
        return FUNC;
    }

    if (strcmp(identifier, "return") == 0)
    {
        return RETURN;
    }

    if (strcmp(identifier, "var") == 0)
    {
        return VAR;
    }

    if (strcmp(identifier, "print") == 0)
    {
        return PRINT;
    }

    if (strcmp(identifier, "TRUE") == 0)
    {
        return TRUE;
    }

    if (strcmp(identifier, "FALSE") == 0)
    {
        return FALSE;
    }

    if (strcmp(identifier, "NULL") == 0)
    {
        return NIL;
    }

    return -1;
}

/**
 *  Parse the identifier.
 */
void identifier(char *code, int *current)
{
    char *start = &(code[*current]);
    char *end = start;

    while (isAlpha(*end))
    {
        end++;
        (*current)++;
    }

    end--;

    int len = end - start + 1;

    char id[len + 1];

    nstrcp(id, start, len);

    LITERAL t = matchIdentifier(id);

    add_token(((int)t < 0) ? IDENTIFIER : t, id);
}

/**
 * Tokenize the code.
 */
TOKEN *tokenize(char *code)
{

    int current = 0;
    char c;

    while (1)
    {
        c = code[current];

        if (!c)
            break;

        switch (c)
        {

        case '"':
            string(code, &current);
            current++;
            break;
        case '+':
            add_token(PLUS, NULL);
            current++;
            break;
        case '-':
            add_token(MINUS, NULL);
            current++;
            break;
        case '*':
            add_token(MULTIPLY, NULL);
            current++;
            break;
        case '/':
            // if we match another '/', then we have a comment.
            if (matchChar(code, &current, "/"))
            {
                // skip
                while (peek(code, &current) != '\n' && peek(code, &current) != '\0')
                    current++;

                current++;
                continue;
            }

            add_token(DIVIDE, NULL);
            current++;

            break;
        case '=':
            add_token(matchChar(code, &current, "=") ? EQUAL_EQUAL : EQUAL, NULL);
            current++;
            break;
        case '!':
            if (matchChar(code, &current, "="))
            {
                add_token(BANG_EQUAL, NULL);
            }
            else
            {
                add_token(NOT, NULL);
            }

            current++;
            break;
        case '>':
            add_token(matchChar(code, &current, "=") ? GREATER_THAN_EQUAL : GREATER_THAN, NULL);
            current++;
            break;
        case '<':
            add_token(matchChar(code, &current, "=") ? LESS_THAN_EQUAL : LESS_THAN, NULL);
            current++;
            break;

        case '{':
            add_token(OPENBRACE, NULL);
            current++;
            break;
        case '}':
            add_token(CLOSEBRACE, NULL);
            current++;
            break;
        case '(':
            add_token(OPENPAREN, NULL);
            current++;
            break;
        case ')':
            add_token(CLOSEPAREN, NULL);
            current++;
            break;
        case '&':

            if (!matchChar(code, &current, "&"))
            {
                raise("Unexpected token &", line);
            }
            current++;
            add_token(AND, NULL);
            break;
        case '|':
            if (!matchChar(code, &current, "|"))
            {
                raise("Unexpected token |", line);
            }
            current++;
            add_token(OR, NULL);
            break;
        case ';':
            add_token(SEMICOLON, NULL);
            current++;
            break;
        case '\t':
        case ' ':
            current++;
            continue;

        case '\n':
            line++;
            current++;
            break;
        default:
            if (isAlpha(c))
            {
                identifier(code, &current);
            }
            else if (isNum(c))
            {
                number(code, &current);
            }
            else
            {
                raise("Unexpected token", line);
            }

            break;
        }
    }
    TOKEN *l = token_list;
    token_list = NULL;
    token_end = NULL;
    line = 1;
    return l;
}
