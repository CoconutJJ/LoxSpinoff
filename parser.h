#ifndef PARSER_H
#define PARSER_H

#include "types.h"
#include "parser/parse_expr.h"
#include "parser/parse_utils.h"

OP *printStatement(TOKEN **curr);

OP *expressionStatement(TOKEN **curr);

OP *parseStatement(TOKEN **curr);

OP **parse(TOKEN **list);

#endif