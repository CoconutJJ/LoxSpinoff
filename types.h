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

typedef enum stmt_t {

    PRINT_STMT,
    

} STATEMENT_TYPE;


typedef enum child_type
{

    BIN,
    UNI,
    LIT

} CHILD_T;

/**
 * Tokens
 */
typedef struct __token
{
    TOKEN *next;
    LITERAL t;
    int line;
    char value[];

} TOKEN;


typedef struct __stmt {

    OP * tree;
} STATEMENT;


/**
 * Parse Tree node
 */
typedef struct __op
{

    LITERAL op;

    /**
     * Define the literal type
     * 
     * BIN - binary operator
     * UNI - unary operator
     * LIT - literal
     * 
     */
    CHILD_T type;

    /**
     * Line number in user file where literal occurred.
     */
    int line;

    /**
     * Only 1 of 3 possible fields should be used, hence the union
     * For Binary operators use the *left and *right struct.
     * For Unary operators use the *next pointer
     * For Numbers/Strings use the i_literal, f_literal struct.
     */
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