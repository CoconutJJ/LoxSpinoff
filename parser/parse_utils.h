#ifndef PARSE_UTIL_H
#define PARSE_UTIL_H
#include "../types.h"

void panic(TOKEN **curr, char *msg);

void error(TOKEN **curr, char *msg);

int matchToken(TOKEN **curr, LITERAL t);

#endif