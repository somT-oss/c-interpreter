#ifndef TOKENS_H
#define TOKENS_H

typedef char* TokenType;

typedef struct {
    char *type; 
    char *literal;
} Token;

void create_keyword_values();
void create_keyword_keys();

#endif