#include "../hashtable/hash_table.h"
#include "../tokens/token.h"
#include "stdbool.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HashTable *KEYWORDS = NULL;
char input[] = "let 20 >= 12";
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
    lexer->readPosition += 1; // Move the character position to be read one step further
}  

void track_back(Lexer *lexer) {
    lexer->readPosition -= 1;
    lexer->position = lexer->readPosition - 1; 
}

void create_keywords() {
    KEYWORDS = create_hashtable();
}

void add_all_keys_and_values() {
    int keyword_keys_length = (int)(sizeof(KEYWORD_KEYS)/sizeof(KEYWORD_KEYS[0]));
    int keyword_values_length = (int)(sizeof(KEYWORD_VALUES)/sizeof(KEYWORD_VALUES[0]));

    if (keyword_keys_length != keyword_values_length) {
        printf("HashTable Keys and Values don't match");
        return;
    }
    
    for (int i = 0; i < keyword_keys_length; i++ ) {
        insert(KEYWORDS, KEYWORD_KEYS[i], KEYWORD_VALUES[i]);
    }
}

void skipWhiteSpace(Lexer *lexer) {
    while (lexer->character == ' ' || lexer->character == '\t' || lexer->character == '\n' || lexer->character == '\r') {
        readChar(lexer);
    }
}

char peekChar(Lexer *lexer) {
    if (lexer->readPosition >= input_length) {
        return 1;
    } else {
        return lexer->input[lexer->readPosition];
    }
} 

bool isLetter(char byte) {
    return 'a' <= byte && byte <= 'z' || 'A' <= byte && byte <= 'Z' || byte == '_';
} 


char *readNumber(Lexer *lexer) {
    int buffer_size = 1;
    int iterator = 0;
    char *value = malloc(buffer_size);

    while (isdigit(lexer->character)) {
        if (iterator >= buffer_size - 1) {
            buffer_size *= 2;
            char *temp = realloc(value, buffer_size);
            if (temp == NULL) {
                printf("Memory allocation failed");
                free(temp);
                free(value); 
            }
            value = temp;
        }
        value[iterator] = lexer->character;
        iterator ++;
        readChar(lexer);
    } 
    value[iterator] = '\0';
    return value;
}


char *readIdentifier(Lexer *lexer) {
    int buffer_size = 1; // Initial buffer size
    int iterator = 0;
    char *identifier = malloc(buffer_size);
    
    if (identifier == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    while (isLetter(lexer->character)) {
        if (iterator >= buffer_size - 1) { // Resize buffer if needed
            buffer_size *= 2;
            char *temp = realloc(identifier, buffer_size);
            if (temp == NULL) {
                free(identifier);
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
            identifier = temp;
        }
        identifier[iterator++] = lexer->character;
        readChar(lexer);
    }
    // printf("buffer_size: %d, iterator: %d ", buffer_size, iterator);
    identifier[iterator] = '\0';
    return identifier;
}   

Token newToken(TokenType tokenType, char *literal) {
    Token token = {
        .type=tokenType,
        .literal=literal
    };
    return token;
}


Token nextToken(Lexer *lexer) {
    Token token; 
    
    skipWhiteSpace(lexer);
    
    char literal[2] = {lexer->character};
    // printf("%s\n", literal);
    switch (lexer->character) {
        default:
            if (isLetter(lexer->character)) {
                token.literal = readIdentifier(lexer);
                track_back(lexer);
                if (search(KEYWORDS, token.literal) == 0) {
                    token.type = get_key(KEYWORDS, token.literal);
                } else {
                    token.type = "IDENT"; 
                }
            } 
            else if (isdigit(lexer->character)) {
                token.type = "INT";
                token.literal = readNumber(lexer);
            }
            break;
        case '=':
            if (peekChar(lexer) == '=') {
                readChar(lexer);
                Token EQ_TOKEN = {
                    "EQUALS_TO",
                    "=="
                }; 
            } else {
                token = newToken("ASSIGN", literal);
            }
            break;
        case '!':
            if (peekChar(lexer) == '=') {
                readChar(lexer);
                Token EQ_TOKEN = {
                    "NOT_EQUALS_TO",
                    "!="
                }; 
            } else {
                token = newToken("BANG", literal);
            }
            break;
        case '>':
            if (peekChar(lexer) == '=') {
                readChar(lexer);
                Token EQ_TOKEN = {
                    "GREATER_THAN_OR_EQUALS_TO",
                    ">="
                }; 
            } else {
                token = newToken("GREATER_THAN", literal);
            }
            break;
        case '<':
            if (peekChar(lexer) == '=') {
                readChar(lexer);
                Token EQ_TOKEN = {
                    "LESS_THAN_OR_EQUALS_TO",
                    "<="
                }; 
            } else {
                token = newToken("LESS_THAN", literal);
            }
            break;
        case ';':
            token = newToken("SEMICOLON", literal);
            break;
        case '+':
            token = newToken("PLUS", literal);
            break;
        case '-':
            token = newToken("MINUS", literal);
            break;
        case '*':
            token = newToken("MULTIPLICATION", literal);
            break;
        case '/':
            token = newToken("DIVISION", literal);
            break;
        case '(':
            token = newToken("LPAREN", literal);
            break;
        case ')':
            token = newToken("RPAREN", literal);
            break;
        case '{':
            token = newToken("LBRACE", literal);
            break;
        case '}':
            token = newToken("RBRACE", literal);
            break;
        case ',':
            token = newToken("COMMA", literal);
            break;
        case 0:
            token = newToken("EOF", "");
            break;
    }
   
    readChar(lexer);
    return token;

}

int main() {

    Lexer lexer = {
     input,
      0,
      0
    };
    printf("%s\n", input);

    create_keywords();
    add_all_keys_and_values();

    readChar(&lexer);
    Token token;
    
    do {
        token = nextToken(&lexer);
        printf("Type: %s, Literal: %s\n", token.type, token.literal);

    } while (strcmp(token.type, "EOF") != 0);

    
    return 0;
}