#ifndef PARSER_H
#define PARSER_H
#include "../tokens/token.h"
#include "../lexers/lexer.h"
#include "../ast/ast.h"


typedef struct Parser {
    Lexer *lexer;
    Token currentToken;
    Token peekToken;
} Parser;

void parseNextToken(Parser *parser);
Program *parseProgram(Parser *parser);

#endif