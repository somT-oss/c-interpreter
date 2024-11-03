#include "tokens.h"
#include <stdio.h>

struct Lexer {
    char *input;
    int position;
    int readPosition;
    char character;
};

void readChar(struct Lexer *lexer) {
    int input_length = (int) (sizeof(&lexer->input)/sizeof(lexer->input[0])); // Get length of input in Lexer struct
    if (lexer->readPosition >= input_length) { // Check if the curr position of the input string on the lexer is greater than the length of the input string 
        lexer->character = 0; // If so, reset character to the begining.
    } else {
        lexer->character = lexer->input[lexer->readPosition]; // Else, update character to the value of the current character read in the input string
    }
    lexer->position = lexer->readPosition; // Updated the position
    lexer->readPosition += 1; // Move the character position to be read one step further
}  


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

    struct Lexer lexer = {
        .input = input,
        .position = 0,
        .readPosition = 0
    };

    for (int i = 0; i < input_length; i ++) {
        readChar(&lexer);
        printf("Current char: %c \n", lexer.character);
    }

    return 0;
}