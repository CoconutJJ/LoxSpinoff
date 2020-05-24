#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "parser/parse_expr.h"
#include "parser/parse_utils.h"

OP *printStatement(TOKEN **curr)
{
    OP *expr = parseExpr(curr);

    if (!matchToken(curr, SEMICOLON))
    {
        panic(curr, "Expected ; after expression");
    }

    OP *printStmt = createUnaryOp(PRINT, expr->line);

    printStmt->next = expr;

    return printStmt;
}

OP *expressionStatement(TOKEN **curr)
{
    OP *expr = parseExpr(curr);

    return expr;
}

OP *parseStatement(TOKEN **curr)
{
    if (matchToken(curr, PRINT))
    {
        return printStatement(curr);
    }

    return expressionStatement(curr);
}



OP **parse(TOKEN **list)
{
    int curr_sz = 5;
    
    int i = 0;
    
    OP **stmts = malloc(2 * sizeof(OP *));
    while (1)
    {
        if (i - 1 == curr_sz) {
            curr_sz *= 2;
            stmts = realloc(stmts, curr_sz * sizeof(OP *));
        }
     
        if (!(*list)) {
            stmts[i] = NULL;
            break;
        }

        OP *stmt = parseStatement(list);
        stmts[i] = stmt;
        i++;
    }

}