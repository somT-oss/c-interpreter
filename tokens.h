#ifndef TOKENS_H
#define TOKENS_H

typedef char* TokenType;

typedef struct {
    char *TokenType; 
    char *literal;
} Token;

#endif