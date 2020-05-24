#ifndef PARSE_EXPR_H
#define PARSE_EXPR_H

#include "../types.h"

OP *createBinaryOp(LITERAL bin_op, int line);

OP *createUnaryOp(LITERAL un_op, int line);

OP *createLiteral(LITERAL lit, int line);

int matchToken(TOKEN **curr, LITERAL t);

OP *parsePrimary(TOKEN **curr);

OP *parseUnary(TOKEN **curr);

OP *parseProducts(TOKEN **curr);

OP *parseSums(TOKEN **curr);

OP *parseComparison(TOKEN **curr);

OP *parseEquality(TOKEN **curr);

OP *parseAND(TOKEN **curr);

OP *parseOR(TOKEN **curr);

OP *parseExpr(TOKEN **tokenList);

#endif