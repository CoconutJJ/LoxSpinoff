# LoxSpinoff

A language developed following the guide of
https://craftinginterpreters.com/the-lox-language.html


## How to use

```git clone https://github.com/CoconutJJ/LoxSpinoff.git```\
```cd LoxSpinoff```\
```make```\
```./interp```

## Documentation

**Files**

`main.c` - interpreter starts here, either launches a REPL if no filename was
passed as an argument or it reads the file contents and copies the code into a
buffer.

`token.c/token.h ` - code is given to the tokenizer where different operators and
keywords such as `print` or `+` are replaced with their C `LITERAL` enum.

`parser.c/parser.h` - The enum token list is passed to the parser where the parse tree is
built.

`interpreter.c/interpreter.h` - Recursive descent. Evaluates the parse tree step by step.

`Makefile` - compiles the code. Run with `make` in the `Makefile` directory  
 
`types.h` - this file contains all the type declarations used in the code. Parse
tree nodes, enum values etc. First place and last place to look when you aren't
sure how a certain type is defined.


## Expression Syntax
`&&`    AND operator\
`||`    OR operator\
`TRUE`  TRUE\
`FALSE` FALSE\
`+`     PLUS\
`-`     MINUS\
`>`     GREATER\
`<`     LESS\



