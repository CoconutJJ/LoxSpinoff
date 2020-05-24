#include <stdio.h>
#include <stdlib.h>
#include "../types.h"
#include "parse_utils.h"

OP *parseOR(TOKEN **tokenList);

OP *createBinaryOp(LITERAL bin_op, int line)
{
    OP *new_op = malloc(sizeof(OP));
    new_op->type = BIN;
    new_op->left = NULL;
    new_op->right = NULL;
    new_op->op = bin_op;
    return new_op;
}

OP *createUnaryOp(LITERAL un_op, int line)
{
    OP *new_op = malloc(sizeof(OP));
    new_op->type = UNI;
    new_op->op = un_op;
    new_op->next = NULL;

    return new_op;
}

OP *createLiteral(LITERAL lit, int line)
{

    OP *new_op = malloc(sizeof(OP));

    new_op->type = LIT;
    new_op->op = lit;
    new_op->f_literal = 0.00;
    new_op->i_literal = 0;

    return new_op;
}

/**
 *  Parses a binary operator that calls leftParse of the left operand and
 *  rightParse on the right operand.
 */
OP *parseBinOp(TOKEN **curr, OP *(*leftParse)(TOKEN **), OP *(*rightParse)(TOKEN **), LITERAL t[], int literal_sz)
{
    OP *left = leftParse(curr); // 5

    if (!left)
    {
        panic(curr, "Invalid Expression");
    }

    TOKEN *curr_token = *curr;
    OP *root = left;

    int has_token = 0;

    while (*curr)
    {

        // ensure at least 1 token matches
        for (int i = 0; i < literal_sz; i++)
        {
            curr_token = *curr;
            if (matchToken(curr, t[i]))
            {
                has_token = 1;
                break;
            }
        }

        if (!has_token)
            break;

        has_token = 0;
        root = createBinaryOp(curr_token->t, curr_token->line); // -
        root->left = left;
        root->right = rightParse(curr);
        if (!root->right)
        {
            panic(curr, "Invalid expression");
        }
        left = root;
    }

    return root;
}

OP *parsePrimary(TOKEN **curr)
{
    if (!(*curr))
        return NULL;

    OP *leaf;
    TOKEN *curr_token = (*curr);

    if (matchToken(curr, FALSE) || matchToken(curr, TRUE))
    {
        leaf = createLiteral(curr_token->t, curr_token->line);
        return leaf;
    }

    if (matchToken(curr, INT))
    {
        leaf = createLiteral(INT, curr_token->line);

        leaf->i_literal = strtol(curr_token->value, NULL, 10);

        return leaf;
    }

    if (matchToken(curr, FLOAT))
    {
        leaf = createLiteral(FLOAT, curr_token->line);

        leaf->f_literal = strtof(curr_token->value, NULL);

        return leaf;
    }

    if (matchToken(curr, NIL))
    {
        leaf = createLiteral(NIL, curr_token->line);
        return leaf;
    }

    if (matchToken(curr, OPENPAREN))
    {
        OP *body = parseOR(curr);

        if (!matchToken(curr, CLOSEPAREN))
        {
            panic(curr, "Expected ')' after expression");
        }

        return body;
    }

    return NULL;
}

OP *parseUnary(TOKEN **curr)
{
    if (!(*curr))
        return NULL;
    TOKEN *curr_token = *curr;
    if (matchToken(curr, NOT) || matchToken(curr, MINUS))
    {

        OP *body = parseUnary(curr);

        OP *root = createUnaryOp(curr_token->t, curr_token->line);
        root->next = body;

        return root;
    }

    return parsePrimary(curr);
}

OP *parseProducts(TOKEN **curr)
{
    LITERAL t[] = {DIVIDE, MULTIPLY};
    return parseBinOp(curr, parseUnary, parseUnary, t, 2);
}

OP *parseSums(TOKEN **curr)
{
    LITERAL t[] = {PLUS, MINUS};
    return parseBinOp(curr, parseProducts, parseProducts, t, 2);
}

OP *parseComparison(TOKEN **curr)
{
    LITERAL t[] = {GREATER_THAN, GREATER_THAN_EQUAL, LESS_THAN, LESS_THAN_EQUAL};
    return parseBinOp(curr, parseSums, parseSums, t, 4);
}

OP *parseEquality(TOKEN **curr)
{
    LITERAL t[] = {EQUAL_EQUAL, BANG_EQUAL};
    return parseBinOp(curr, parseComparison, parseComparison, t, 2);
}

OP *parseAND(TOKEN **curr)
{
    LITERAL t[] = {AND};
    return parseBinOp(curr, parseEquality, parseEquality, t, 2);
}

OP *parseOR(TOKEN **curr)
{
    LITERAL t[] = {OR};
    return parseBinOp(curr, parseAND, parseAND, t, 2);
}
OP *parseExpr(TOKEN **tokenList)
{

    OP *tree = parseOR(tokenList);

    return tree;
}