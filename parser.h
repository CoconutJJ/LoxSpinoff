#ifndef PARSER_H
#define PARSER_H

#include "types.h"

void panic(TOKEN **curr);

OP *createBinaryOp(LITERAL bin_op);

OP *createUnaryOp(LITERAL un_op);

OP *createLiteral(LITERAL lit);

int matchToken(TOKEN **curr, LITERAL t);

OP *parsePrimary(TOKEN **curr);

OP *parseUnary(TOKEN **curr);

OP *parseProducts(TOKEN **curr);

OP *parseSums(TOKEN **curr);

OP *parseComparison(TOKEN **curr);

OP *parseEquality(TOKEN **curr);

OP *parseLogic(TOKEN **curr);

OP *parse(TOKEN *tokenList);

#endif