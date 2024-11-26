#include "../tokens/token.h"

#ifndef LEXER_H
#define LEXER_H

typedef struct {
    char *input;
    int position;
    int readPosition;
    char character;
}  Lexer;


extern char *input;
#define  input_length 2048

Token nexToken(Lexer *lexer);
void initiate_lexer();

#endif
