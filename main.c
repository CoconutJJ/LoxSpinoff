#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "parser.h"
#include "types.h"
void interpret(char * code) {

    TOKEN * tokens = tokenize(code);

    OP * parseTree = parse(&tokens);

    return;
}


int main(int argc, char** argv) {

    /* TODO: Not Implemented. This is just so make won't complain */
    
    if (argc == 2) {

        FILE * script = fopen(argv[1], "r");

        if (!script) {
            perror("interpreter: fopen");
            exit(EXIT_FAILURE);
        }

        fseek(script, 0, SEEK_END);

        int f_sz = ftell(script);

        fseek(script, 0, SEEK_SET);

        char code[f_sz];

        if (fread(code, f_sz, 1, script) != f_sz) {
            perror("interpreter: fread");
            exit(EXIT_FAILURE);
        }

        interpret(code);
    } else if (argc == 1) {
        
        printf("\nLoxSpinoff Shell\n");
        printf("Author: David Yue <david.yue@mail.utoronto.ca>\n");
        printf("Press Ctrl+C to exit.\n");
        
        char line[1024];
        while (1) {
            printf(">>> ");
            if (fgets(line, 1024, stdin) == NULL) {
                break;
            }
            printf("%s", line);
            interpret(line);

        }

    }





}