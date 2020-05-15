#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "types.h"

int isTruthy(EVAL p);

void runtimeError(OP *root, char *msg);

EVAL evaluateExpr(OP *parseTree);
#endif