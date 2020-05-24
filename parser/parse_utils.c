
#include <stdio.h>
#include <stdlib.h>
#include "../types.h"

void panic(TOKEN **curr, char *msg)
{

    TOKEN *curr_token = *curr;

    if (!curr_token)
    {
        fprintf(stderr, "last line: %s", msg);
    }
    else
    {
        fprintf(stderr, "line %d: %s", curr_token->line, msg);
    }

    while (curr_token)
    {

        switch (curr_token->t)
        {
        case IF:
        case WHILE:
        case FOR:
        case SEMICOLON:
        case FUNC:
            return;
            break;
        default:
            curr_token = curr_token->next;
            *curr = curr_token;
            break;
        }
    }

    exit(EXIT_FAILURE);
}

void error(TOKEN **curr, char *msg)
{

    fprintf(stderr, "line %d: %s", (*curr)->line, msg);
    exit(EXIT_FAILURE);
}



int matchToken(TOKEN **curr, LITERAL t)
{

    if (!(*curr))
        return 0;

    if ((*curr)->t == t)
    {
        *curr = (*curr)->next;
        return 1;
    }
    return 0;
}