#include "hash_table.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char input[] = "let new_name == 5 + 5 ";
int input_length = (int)(sizeof(input)/sizeof(input[0]));

typedef struct {
    char *input;
    int position;
    int readPosition;
    char character;
}  Lexer;

char *KEYWORD_VALUES[] = {
    "FUNCTION",
    "LET",
    "TRUE",
    "FALSE",
    "IF",
    "ELSE",
    "RETURN",
}; 

char *KEYWORD_KEYS[] = {
    "fn",
    "let",
    "true",
    "false",
    "if",
    "else",
    "return"
};


void readChar(Lexer *lexer) {
    // printf("%d\n", (int)(sizeof(&lexer->input)));
    // int input_length = (int) (sizeof(&lexer->input)/sizeof(lexer->input[0])); // Get length of input in Lexer struct
    if (lexer->readPosition >= input_length) { // Check if the curr position of the input string on the lexer is greater than the length of the input string 
        lexer->character = 0; // If so, reset character to the begining.
    } else {
        lexer->character = lexer->input[lexer->readPosition]; // Else, update character to the value of the current character read in the input string
    }
    lexer->position = lexer->readPosition; // Updated the position
    lexer->readPosition += 1
; // Move the character position to be read one step further
}  

char peekChar(Lexer *lexer) {
    if (lexer->readPosition >= input_length) {
        return 1;
    } else {
        return lexer->input[lexer->readPosition];
    }
} 


void nextToken(Lexer lexer, HashTable *hashtable) {
    int iterator = 0;
    int token_buffer_size = 1;
    char *token_buffer = malloc(token_buffer_size);
    char *token;
    int token_counter = 0;

    while (iterator <= input_length) { 
        readChar(&lexer);

        if (isspace(lexer.character) || lexer.character == '\t' || lexer.character == '\n' || lexer.character == '\r') { 
            token_buffer[token_counter] = '\0'; 
            token_counter = 0;  

            // printf("%s\n", token_buffer);
            if (strcmp(token_buffer, "=") == 0) {
                printf("I am here");
                // if (peekChar(&lexer) == '=') {
                //     printf("{Type:%s Literal:%s} \n", "==", "==");
                // }  else {
                //     printf("{Type:%c Literal:%c} \n", lexer.character, lexer.character);
                // }
            }

            else if (strcmp(token_buffer, "!") == 0) {
                printf("I am here");
                // if (peekChar(&lexer) == '=') {
                //     printf("{Type:%s Literal:%s} \n", "!=", "==");
                // } else {
                //     printf("{Type:%c Literal:%c} \n", lexer.character, lexer.character);
                // }
            }

            else if (search(hashtable, token_buffer) == 0) {
                printf("{Type:%s Literal:%s} \n", token_buffer, token_buffer);
            } 
            else {
                printf("{Type:%s Literal:%s} \n", "IDENT", token_buffer);
            }
        }
        else { 
                if (token_counter >= token_buffer_size - 1) { 
                token_buffer_size *= 2;
                char *temp = realloc(token_buffer, token_buffer_size);  
                if (temp == NULL) { 
                    free(token_buffer);
                    printf("Memory allocation failed\n"); 
                    return;
                }
                token_buffer = temp;
            }
            token_buffer[token_counter] = lexer.character;
            token_counter ++;
        }
        iterator ++;
    } 
    free(token_buffer);
}

int main() {
    HashTable *keywords = create_hashtable();
    int keyword_keys_length = (int)(sizeof(KEYWORD_KEYS)/sizeof(KEYWORD_KEYS[0]));
    int keyword_values_length = (int)(sizeof(KEYWORD_VALUES)/sizeof(KEYWORD_VALUES[0]));

    if (keyword_keys_length != keyword_values_length) {
        printf("HashTable Keys and Values don't match");
        return 1;
    }
    for (int i = 0; i < keyword_keys_length; i++) {
        insert(keywords, KEYWORD_KEYS[i], KEYWORD_VALUES[i]);
    }

    Lexer lexer = {
     input,
      0,
      0
    };
    
    nextToken(lexer, keywords);
    delete_table(keywords);
}