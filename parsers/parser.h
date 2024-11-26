#ifndef PARSER_H
#define PARSER_H
#include "../tokens/token.h"
#include "../lexers/lexer.h"


typedef struct Parser {
    Lexer *lexer;
    Token currentToken;
    Token peekToken;
} Parser;


#endif