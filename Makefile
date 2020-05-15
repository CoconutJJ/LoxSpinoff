GCC= gcc -Wall

all: main clean

main: parser.o token.o interpreter.o
	$(GCC) main.c parser.o token.o interpreter.o -o interp

parser.o: parser.c
	$(GCC) -c parser.c

token.o: token.c
	$(GCC) -c token.c

interpreter.o: interpreter.c
	$(GCC) -c interpreter.c

.PHONY: clean

clean:
	rm parser.o token.o interpreter.o