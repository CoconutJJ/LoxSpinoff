#include <stdio.h>
#include <stdlib.h>
#include "types.h"

OP *parse(TOKEN **tokenList);

void panic(TOKEN **curr)
{

    TOKEN *curr_token = *curr;

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
            break;
        }
    }

    *curr = curr_token;
}

OP *createBinaryOp(LITERAL bin_op)
{
    OP *new_op = malloc(sizeof(OP));
    new_op->type = BIN;
    new_op->left = NULL;
    new_op->right = NULL;
    new_op->op = bin_op;
    return new_op;
}

OP *createUnaryOp(LITERAL un_op)
{
    OP *new_op = malloc(sizeof(OP));
    new_op->type = UNI;
    new_op->op = un_op;
    new_op->next = NULL;

    return new_op;
}

OP *createLiteral(LITERAL lit)
{

    OP *new_op = malloc(sizeof(OP));

    new_op->type = LIT;
    new_op->op = lit;
    new_op->f_literal = 0.00;
    new_op->i_literal = 0;

    return new_op;
}

int matchToken(TOKEN **curr, LITERAL t)
{

    if ((*curr)->t == t)
    {
        *curr = (*curr)->next;
        return 1;
    }
    return 0;
}

OP *parsePrimary(TOKEN **curr)
{
    OP *leaf;
    TOKEN *curr_token = (*curr);

    if (matchToken(curr, FALSE) || matchToken(curr, TRUE))
    {
        leaf = createLiteral(curr_token->t);
        return leaf;
    }

    if (matchToken(curr, INT))
    {
        leaf = createLiteral(INT);

        leaf->i_literal = strtol(curr_token->value, NULL, 10);

        return leaf;
    }

    if (matchToken(curr, FLOAT))
    {
        leaf = createLiteral(FLOAT);

        leaf->f_literal = strtof(curr_token->value, NULL);

        return leaf;
    }

    if (matchToken(curr, NIL))
    {
        leaf = createLiteral(NIL);
        return leaf;
    }

    if (matchToken(curr, OPENPAREN))
    {
        OP *body = parse(curr);

        if (!matchToken(curr, CLOSEPAREN))
        {
            fprintf(stderr, "Expected ')' after expression");
            exit(EXIT_FAILURE);
        }

        return body;
    }

    return NULL;
}

OP *parseUnary(TOKEN **curr)
{

    if (matchToken(curr, NOT) || matchToken(curr, MINUS))
    {

        OP *body = parseUnary(curr);

        OP *root = createUnaryOp((*curr)->t);
        root->next = body;

        return root;
    }

    return parsePrimary(curr);
}

OP *parseProducts(TOKEN **curr)
{
    OP *left = parseProducts(curr);
    OP *root = left;

    TOKEN *curr_token = *curr;

    while (1)
    {
        if (!(
                matchToken(curr, PLUS) || matchToken(curr, MINUS)))
            break;

        root = createBinaryOp(curr_token->t);
        root->left = left;
        root->right = parseProducts(curr);
        left = root;
    }
    return root;
}

OP *parseSums(TOKEN **curr)
{
    OP *left = parseProducts(curr);
    OP *root = left;

    TOKEN *curr_token = *curr;

    while (1)
    {
        if (!(
                matchToken(curr, PLUS) || matchToken(curr, MINUS)))
            break;

        root = createBinaryOp(curr_token->t);
        root->left = left;
        root->right = parseProducts(curr);
        left = root;
    }
    return root;
}

OP *parseComparison(TOKEN **curr)
{
    OP *left = parseSums(curr);
    OP *root = left;

    TOKEN *curr_token = *curr;

    while (1)
    {

        if (!(
                matchToken(curr, GREATER_THAN) || matchToken(curr, GREATER_THAN_EQUAL) || matchToken(curr, LESS_THAN) || matchToken(curr, LESS_THAN_EQUAL)))
            break;

        root = createBinaryOp(curr_token->t);

        root->left = left;
        root->right = parseSums(curr);
        left = root;
    }

    return root;
}

OP *parseEquality(TOKEN **curr)
{

    OP *left = parseComparison(curr);

    TOKEN *curr_token = *curr;
    OP *root = left;

    while (1)
    {

        if (!matchToken(curr, EQUAL_EQUAL) && !matchToken(curr, BANG_EQUAL))
            break;

        root = createBinaryOp(curr_token->t);
        root->left = left;
        root->right = parseComparison(curr);
        left = root;
    }

    return root;
}

OP *parseLogic(TOKEN **curr)
{

    OP *left = parseEquality(curr);

    TOKEN *curr_token = *curr;

    OP *root = left;

    while (1)
    {
        if (!(matchToken(curr, AND) || matchToken(curr, OR)))
            break;

        root = createBinaryOp(curr_token->t);

        root->left = left;

        root->right = parseEquality(curr);

        left = root;
    }

    return root;
}

OP *parse(TOKEN **tokenList)
{

    TOKEN *curr = *tokenList;
}
