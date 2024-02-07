#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h> // Include bool type
#define MAX_LENGTH 100

// Token types
typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_OPERATOR,
    TOKEN_INTEGER,
    TOKEN_SPCHAR,
    TOKEN_BRACKET,
    TOKEN_STRING,
    TOKEN_STATEMENT,
    TOKEN_UNKNOWN,
    TOKEN_EOF
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char lexeme[MAX_LENGTH];
} Token;

// Function to check for a delimiter
bool isDelimiter(char chr) {
    return (chr == ',' || chr == ';' || chr == ':');
}

// Function to check for a Bracket
bool isBracket(char chr) {
    return (chr == '(' || chr == ')' || chr == '[' || chr == ']' || chr == '{' || chr == '}');
}

// Function to check for an operator
bool isOperator(char chr) {
    return (chr == '+' || chr == '-' || chr == '*' || chr == '/' || chr == '=' || chr == '<' || chr == '>');
}

// Function to check for a valid identifier
bool isValidIdentifier(char* str) {
    return (isalpha(str[0]) || str[0] == '_');
}

// Function to check for a keyword
bool isKeyword(char* str) {
    const char* keywords[] = {"if", "else", "while", "for", "int", "float", "in", "return"};
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Function to check for an integer
bool isInteger(char* str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    int i = 0;
    while (isdigit(str[i])) {
        i++;
    }
    return str[i] == '\0';
}

// Function for lexical analysis
Token getNextToken(FILE* file) {
    Token token;
    int c = fgetc(file);

    // Skip whitespaces and comments
    while (c == ' ' || c == '\t' || c == '\n') {
        c = fgetc(file);
    }

    // Identify token type
    if (c == EOF) {
        token.type = TOKEN_EOF;
    } else if (isBracket(c)) {
        sprintf(token.lexeme, "%c", c);
        token.type = TOKEN_BRACKET;
    } else if (isDelimiter(c)) {
        sprintf(token.lexeme, "%c", c);
        token.type = TOKEN_SPCHAR;  // Delimiter is treated as unknown
    } else if (isOperator(c)) {
        sprintf(token.lexeme, "%c", c);
        token.type = TOKEN_OPERATOR;
    } else if (isalpha(c) || c == '_') {
        int i = 0;
        while (isalnum(c) || c == '_') {
            token.lexeme[i++] = c;
            c = fgetc(file);
        }
        ungetc(c, file);
        token.lexeme[i] = '\0';

        if (isKeyword(token.lexeme)) {
            token.type = TOKEN_KEYWORD;
        } else if (isValidIdentifier(token.lexeme)) {
            token.type = TOKEN_IDENTIFIER;
        } else {
            token.type = TOKEN_UNKNOWN;
        }
    } else if (isdigit(c)) {
        int i = 0;
        while (isdigit(c)) {
            token.lexeme[i++] = c;
            c = fgetc(file);
        }
        ungetc(c, file);
        token.lexeme[i] = '\0';

        if (isInteger(token.lexeme)) {
            token.type = TOKEN_INTEGER;
        } else {
            token.type = TOKEN_UNKNOWN;
        }
    } else if (c == '"') { // Check if the character is a double quote
        int i = 0;
        token.lexeme[i++] = c; // Include the starting double quote
        c = fgetc(file);
        while (c != '"') { // Keep reading until the closing double quote
            if (c == EOF) {
                fprintf(stderr, "Error: Unterminated string literal\n");
                exit(1);
            }
            token.lexeme[i++] = c;
            c = fgetc(file);
        }
        token.lexeme[i++] = c; // Include the closing double quote
        token.lexeme[i] = '\0';
        token.type = TOKEN_STRING; // Treat the string literal as an operator
    } else if (c == '#') {
		printf("\n");//Aiwee hiii 
        int i = 0;
        token.lexeme[i++] = c; // Include the starting double quote
        c = fgetc(file);
        while (c != '\n') { // Keep reading until the closing double quote
            if (c == EOF) {
                fprintf(stderr, "Error: Unterminated string literal\n");
                exit(1);
            }
            token.lexeme[i++] = c;
            c = fgetc(file);
        }
        token.lexeme[i] = '\0';
        token.type = TOKEN_STATEMENT;
    } else {
        sprintf(token.lexeme, "%c", c);
        token.type = TOKEN_UNKNOWN;
    }

    return token;
}


int main() {
    FILE* file = fopen("test.py", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    Token token;
    do {
        token = getNextToken(file);
        printf("Token: %s, Lexeme: %s\n", token.type == TOKEN_SPCHAR ? "SP_CHAR" : (token.type == TOKEN_UNKNOWN ? "UNKNOWN" : (token.type == TOKEN_STATEMENT ? "STATEMENT" : (token.type == TOKEN_STRING ? "STRING" : (token.type == TOKEN_BRACKET ? "BRACKET" : (token.type == TOKEN_EOF ? "EOF" : (token.type == TOKEN_IDENTIFIER ? "IDENTIFIER" : (token.type == TOKEN_KEYWORD ? "KEYWORD" : (token.type == TOKEN_OPERATOR ? "OPERATOR" : "INTEGER")))))))), token.lexeme);
    } while (token.type != TOKEN_EOF);

    fclose(file);
    return 0;
}

