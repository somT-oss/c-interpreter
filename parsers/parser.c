#include "../lexers/lexer.h"
#include "../ast/ast.h"
#include <stdlib.h>
#include "parser.h"


void parseNextToken(Parser *parser) {
    parser->currentToken = parser->peekToken;
    parser->peekToken = nexToken(parser->lexer);
}

Program *parseProgram(Parser *parser) {
    Program *program = malloc(sizeof(Program));
    if (program != NULL) {
        return program;
    } else {
        return NULL;
    }
}
