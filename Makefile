all: clean

main: parser.o token.o
	gcc -Wall main.c parser.o token.o -o interp

parser: parser.c
	gcc -Wall -c parser.c

token: token.c
	gcc -Wall -c token.c

.PHONY: clean

clean:
	rm parser.o token.o