#ifndef TOKENS_H
#define TOKENS_H

typedef char* TokenType;

typedef struct {
    char *type; 
    char *literal;
} Token;

#endif