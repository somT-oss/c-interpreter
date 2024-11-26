#include "../lexers/lexer.h"
#include "ast.h"
#include <stdlib.h>
#include <time.h>


char *getTokenLiteral(Program *program) {
    if (program->programLength < 0 || program->programStatement == NULL) {
        return NULL;
    }
    Statement *statement = program->programStatement;
    if (statement == NULL) {
        return NULL;
    } else {
        return statement->statementNode->tokenLiteral;
    }
}

