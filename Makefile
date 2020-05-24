GCC = gcc -Wall -Os -s -pedantic

OBJ_FILES = parser.o parse_expr.o parse_utils.o token.o interpreter.o

all: main clean

main: $(OBJ_FILES)
	$(GCC) main.c $(OBJ_FILES) -o interp

parser.o: parser.c
	$(GCC) -c parser.c 

parse_expr.o: parser/parse_expr.c
	$(GCC) -c parser/parse_expr.c

parse_utils.o: parser/parse_utils.c
	$(GCC) -c parser/parse_utils.c

token.o: tokenizer/token.c
	$(GCC) -c tokenizer/token.c

interpreter.o: interpreter.c
	$(GCC) -c interpreter.c

.PHONY: clean

clean:
	rm $(OBJ_FILES)