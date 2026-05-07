#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

// Token Definitions
typedef enum {
    TK_IF, TK_ELSE, TK_WHILE, TK_END, TK_THEN, TK_PRINT,
    TK_ID, TK_INT, TK_FLOAT, 
    TK_PLUS, TK_MINUS, TK_MUL, TK_DIV, TK_ASSIGN,
    TK_LPAREN, TK_RPAREN, TK_EOF, TK_ERROR
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[32];
    double value;
    int line;
} Token;

// Global State (Declared as extern to be shared)
extern Token current_token;
extern FILE *source;
extern int line_num;

// Function Prototypes
void advance();
void parse();
void statement();
void error(const char* msg);

#endif