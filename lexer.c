#include "tokens.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char input[] = "let x = 5 + 5";
int input_length = (int)(sizeof(input)/sizeof(input[0]));

typedef struct {
    char *input;
    int position;
    int readPosition;
    char character;
}  Lexer;

void readChar(Lexer *lexer) {
    // printf("%d\n", (int)(sizeof(&lexer->input)));
    // int input_length = (int) (sizeof(&lexer->input)/sizeof(lexer->input[0])); // Get length of input in Lexer struct
    if (lexer->readPosition >= input_length) { // Check if the curr position of the input string on the lexer is greater than the length of the input string 
        lexer->character = 0; // If so, reset character to the begining.
    } else {
        lexer->character = lexer->input[lexer->readPosition]; // Else, update character to the value of the current character read in the input string
    }
    lexer->position = lexer->readPosition; // Updated the position
    lexer->readPosition += 1; // Move the character position to be read one step further
}  

int main() {
    
    TokenType ASSIGN = "="; 
    TokenType PLUS = "+"; 
    TokenType LPAREN = "("; 
    TokenType RPAREN = ")"; 
    TokenType LBRACE = "{"; 
    TokenType RBRACE = "}"; 
    TokenType COMMA = ","; 
    TokenType COLON = ";"; 
    TokenType END_OF_LINE = ""; 
    
     // Removed the minus 1 and added EOF TokenType


    Lexer lexer = {
     input,
      0,
      0
    };

    int iterator = 0;
    char *token_buffer;
    int token_buffer_size = 1;
    int token_counter = 0;
    int space_counter = 0;

    while (iterator <= input_length) { // Iterate till '\0'
        readChar(&lexer); // Keep reading characters
        if (isspace(lexer.character) ) { // check if a character is a space
            token_buffer[token_counter] = '\0'; // Null-terminate the token
            printf("%s\n", token_buffer); // Print the current token
            token_counter = 0; // Reset token counter for the next token 
        }else { 
                if (token_counter >= token_buffer_size - 1) { 
                token_buffer_size *= 2; // update buffer size
                char *temp = realloc(token_buffer, token_buffer_size); // reallocate memory based on the new buffer size 
                if (temp == NULL) { 
                    free(token_buffer);
                    printf("Memory allocation failed\n"); // handle memeory allocation error
                    return 1;
                }
                token_buffer = temp; // update the pointer with the newly allocated buffer space
            }
            token_buffer[token_counter] = lexer.character; // add the character to token_buffer
            token_counter ++; // move token_counter
        }
        iterator ++; // always iterate through the string
    }
    return 0;
}