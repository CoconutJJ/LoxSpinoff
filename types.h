#ifndef TYPE_H
#define TYPE_H

typedef struct __token TOKEN;
typedef struct __op OP;
typedef struct __literal_node LITERAL_NODE;

typedef enum literals
{
    IF,
    ELSE,
    WHILE,
    FOR,
    VAR,
    IDENTIFIER,
    STRING,
    INT,
    FLOAT,
    PRINT,
    TRUE,
    FALSE,
    NOT,
    AND,
    OR,
    NIL,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    FUNC,
    RETURN,
    OPENBRACE,
    CLOSEBRACE,
    OPENPAREN,
    CLOSEPAREN,
    EQUAL,
    EQUAL_EQUAL,
    BANG_EQUAL,
    GREATER_THAN,
    LESS_THAN,
    GREATER_THAN_EQUAL,
    LESS_THAN_EQUAL,
    SEMICOLON

} LITERAL;

typedef enum child_type
{

    BIN,
    UNI,
    LIT

} CHILD_T;

typedef struct __token
{
    TOKEN *next;
    LITERAL t;
    int line;
    char value[];

} TOKEN;

typedef struct __op
{

    LITERAL op;
    CHILD_T type;
    int line;
    union
    {
        struct
        {
            OP *left;
            OP *right;
        };
        OP *next;
        struct
        {
            int i_literal;
            float f_literal;
        };
    };

} OP;

typedef struct __eval
{
    LITERAL op;
    union
    {
        int i_literal;
        float f_literal;
    };

} EVAL;

#endif