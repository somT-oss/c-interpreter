#include "hash_table.h"
#include "tokens.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    lexer->readPosition += 1
; // Move the character position to be read one step further
}  


void nextToken(Lexer lexer) {
    int iterator = 0;
    int token_buffer_size = 1;
    char *token_buffer;
    char *token;
    int token_counter = 0;

    while (iterator <= input_length) { 
        readChar(&lexer);
        if (isspace(lexer.character) || lexer.character == '\0' ) { 
            token_buffer[token_counter] = '\0'; 
            token_counter = 0;  
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

    printf("Creating hashtable\n");
    HashTable *identifierHashTable = create_hashtable();
    
    insert(identifierHashTable, "key", "value");
    // insert(identifierHashtable, "chibu", "23");
    // insert(identifierHashtable, fruits[1], fruits[2]);


    Lexer lexer = {
     input,
      0,
      0
    };
    
    nextToken(lexer);

    // print_hashtable(identifierHashtable);
    delete_table(identifierHashTable);
}