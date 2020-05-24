#include <stdio.h>
#include <stdlib.h>
#include "types.h"

void runtimeError(OP *root, char *msg)
{
    fprintf(stderr, "line %d: Runtime Error: %s", root->line, msg);
    exit(EXIT_FAILURE);
}

int isTruthy(EVAL p)
{

    switch (p.op)
    {
    case INT:
        if (p.i_literal != 0)
            return 1;
        break;
    case FLOAT:
        if (p.f_literal != 0.00)
            return 1;
        break;
    case TRUE:
        return 1;
    case FALSE:
        return 0;
    default:
        return -1;
        break;
    }
    return 0;
}

int isLess(EVAL l, EVAL r)
{

    switch (l.op)
    {
    case INT:
        return l.i_literal < r.i_literal;
        break;
    case FLOAT:
        return l.f_literal < r.f_literal;
        break;
    case TRUE:
        return 0;
    case FALSE:
        return 1 && (l.op != r.op);

    default:
        return -1;
        break;
    }
}

int isGreater(EVAL l, EVAL r)
{
    switch (l.op)
    {
    case INT:
        return l.i_literal > r.i_literal;
        break;
    case FLOAT:
        return l.f_literal > r.f_literal;
        break;
    case TRUE:
        return 1 && (l.op != r.op);

    case FALSE:
        return 0;

    default:
        return -1;

    }
}

int isEqual(EVAL l, EVAL r)
{

    if (l.op != r.op)
        return 0;

    switch (l.op)
    {
    case INT:
        return l.i_literal == r.i_literal;
        break;
    case FLOAT:
        return l.f_literal == r.f_literal;
        break;
    case TRUE:
    case FALSE:
        return 1;

    default:
        return -1;
        break;
    }
}


EVAL evaluateExpr(OP *parseTree)
{
    EVAL p, l, r;

    if (parseTree->type == LIT)
    {
        p.op = parseTree->op;
        switch (parseTree->op)
        {
        case INT:
            p.i_literal = parseTree->i_literal;
            break;
        case FLOAT:
            p.f_literal = parseTree->f_literal;
            break;
        case TRUE:
        case FALSE:
            break;
        default:
            runtimeError(parseTree, "Unknown Literal");
            break;
        }
    }

    if (parseTree->type == UNI)
    {
        switch (parseTree->op)
        {
        case NOT:
            p.op = isTruthy(evaluateExpr(parseTree->next)) ? FALSE : TRUE;
            break;
        case MINUS:;
            EVAL body = evaluateExpr(parseTree->next);

            if (body.op == INT)
            {
                p.op = INT;
                p.i_literal = 0 - (body.i_literal);
            }

            if (body.op == FLOAT)
            {
                p.op = FLOAT;
                p.f_literal = (float)0.0 - (body.f_literal);
            }
            break;
        break;
        default:
            break;
        }
    }
    if (parseTree->type == BIN)
    {
        switch (parseTree->op)
        {
        case AND:

            p.op = (isTruthy(evaluateExpr(parseTree->left)) && isTruthy(evaluateExpr(parseTree->right))) ? TRUE : FALSE;
            break;
        case OR:
            p.op = (isTruthy(evaluateExpr(parseTree->left)) || isTruthy(evaluateExpr(parseTree->right))) ? TRUE : FALSE;
            break;
        case EQUAL_EQUAL:;
            l = evaluateExpr(parseTree->left);
            r = evaluateExpr(parseTree->right);

            int isEq = isEqual(l, r);

            if (isEq < 0)
                runtimeError(parseTree, "incompatible type binary operator '=='");

            p.op = isEq ? TRUE : FALSE;

            break;
        case GREATER_THAN:
        case GREATER_THAN_EQUAL:
            l = evaluateExpr(parseTree->left);
            r = evaluateExpr(parseTree->right);

            int isGt = isGreater(l, r) || (parseTree->op == GREATER_THAN_EQUAL ? isEqual(l, r) : 0);

            if (isGt < 0)
                runtimeError(parseTree, "incompatible type binary operator '=='");

            p.op = isGt ? TRUE : FALSE;
            break;
        case LESS_THAN:
        case LESS_THAN_EQUAL:
            l = evaluateExpr(parseTree->left);
            r = evaluateExpr(parseTree->right);

            int isLt = isLess(l, r) || (parseTree->op == LESS_THAN_EQUAL ? isEqual(l, r) : 0);

            if (isLt < 0)
                runtimeError(parseTree, "incompatible type binary operator '=='");

            p.op = isLt ? TRUE : FALSE;
            break;
        case PLUS:; // <-- semicolon here is very important, gcc complains if declaration follows immediately after label.

            l = evaluateExpr(parseTree->left);
            r = evaluateExpr(parseTree->right);

            if (l.op != INT && l.op != FLOAT)
            {
                runtimeError(parseTree->left, "incompatible type for binary operator '+'");
            }

            if (r.op != INT && r.op != FLOAT)
            {
                runtimeError(parseTree->right, "incompatible type binary operator '+'");
            }

            if (r.op == INT && l.op == INT)
            {

                p.op = INT;
                p.i_literal = l.i_literal + r.i_literal;
            }
            else
            {
                float lf, rf;

                lf = (float)(l.op == FLOAT ? l.f_literal : l.i_literal);
                rf = (float)(r.op == FLOAT ? r.f_literal : r.i_literal);

                p.op = FLOAT;
                p.f_literal = lf + rf;
            }

            break;
        case MINUS:;
            l = evaluateExpr(parseTree->left);
            r = evaluateExpr(parseTree->right);

            if (l.op != INT && l.op != FLOAT)
            {
                runtimeError(parseTree->left, "incompatible type binary operator '-'");
            }

            if (r.op != INT && r.op != FLOAT)
            {
                runtimeError(parseTree->right, "incompatible type binary operator '-'");
            }

            if (r.op == INT && l.op == INT)
            {

                p.op = INT;
                p.i_literal = l.i_literal - r.i_literal;
            }
            else
            {
                float lf, rf;

                lf = (float)(l.op == FLOAT ? l.f_literal : l.i_literal);
                rf = (float)(r.op == FLOAT ? r.f_literal : r.i_literal);

                p.op = FLOAT;
                p.f_literal = lf - rf;
            }
            break;
        default:
            break;
        }
    }
    return p;
}