#include <stdio.h>
#include <stdlib.h>
#include <editline.h>
#include "../lexers/lexer.h"


char *input;

int main(int argc, char **argv) {

    printf("Monkey Language Version 0.0.1 \n");
    printf("Press Ctrl+c to Exist \n\n");

    while (1) {
        input = readline(">>> ");
        add_history(input);
        
        printf("\n");
        initiate_lexer();
        
        printf("\n");

        free(input);
    }


    return 0;
}
