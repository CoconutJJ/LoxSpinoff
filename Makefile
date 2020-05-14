GCC= gcc -g -Wall

all: main clean

main: parser.o token.o
	$(GCC) main.c parser.o token.o -o interp

parser.o: parser.c
	$(GCC) -c parser.c

token.o: token.c
	$(GCC) -c token.c

.PHONY: clean

clean:
	rm parser.o token.o