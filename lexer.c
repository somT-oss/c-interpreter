#include "tokens.h"
#include <stdio.h>

int main() {
    char input[] = "=+(){},;";
    
    TokenType ASSIGN = "="; 
    TokenType PLUS = "+"; 
    TokenType LPAREN = "("; 
    TokenType RPAREN = ")"; 
    TokenType LBRACE = "{"; 
    TokenType RBRACE = "}"; 
    TokenType COMMA = ","; 
    TokenType COLON = ";"; 
    TokenType END_OF_LINE = ""; 
    
    TokenType token_type_arr[] = {ASSIGN, PLUS, LPAREN, RPAREN, LBRACE, RBRACE, COMMA, COLON, END_OF_LINE};

    int input_length = (int)(sizeof(input)/sizeof(input[0])); // Removed the minus 1 and added EOF TokenType
    int token_type_arr_length = (int)(sizeof(token_type_arr)/sizeof(token_type_arr[0]));

    if (input_length != token_type_arr_length) {
        printf("Invalid length for both input and token type arr\n");
        printf("input arr len: %d\n", input_length);
        printf("toke type arr len: %d\n", token_type_arr_length);
        return 1;
    }

    for (int i = 0; i < (int)(sizeof(input)/sizeof(input[0])) - 1 ; i ++) {
        if (input[i] != token_type_arr[i][0]) {
            printf("Invalid token at position %d\n", i);
            return 1;
        }
        
    }
    return 0;
}