#ifndef AST_H
#define AST_H 
#include "../tokens/token.h"

typedef struct Node {
    char *tokenLiteral;
} Node;

typedef struct Statement {
    Node *statementNode;
} Statement;

typedef struct Expression {
    Node *expressionNode;
} Expression;

typedef struct Program {
    Statement *programStatement;
    int programLength;
} Program;

typedef struct Identifier {
    Token token;
    char *value;
} Identifier;


typedef struct LetStatement {
    Token token;
    Identifier name;
    Expression value; 
} LetStatement; 


#endif