#include "../include/compiler.h"

int line_num = 1;
Token current_token;
FILE *source = NULL;

void error(const char* msg) {
    printf("Error at line %d: %s (Lexeme: %s)\n", line_num, msg, current_token.lexeme);
    current_token.type = TK_ERROR;
}

void advance() {
    int c = fgetc(source);
    while (isspace(c)) {
        if (c == '\n') line_num++;
        c = fgetc(source);
    }

    if (c == EOF) {
        current_token.type = TK_EOF;
        return;
    }

    if (isalpha(c)) {
        int len = 0;
        while (isalnum(c) || c == '_') {
            if (len < 31) current_token.lexeme[len++] = c;
            c = fgetc(source);
        }
        ungetc(c, source);
        current_token.lexeme[len] = '\0';

        if (strcmp(current_token.lexeme, "if") == 0) current_token.type = TK_IF;
        else if (strcmp(current_token.lexeme, "then") == 0) current_token.type = TK_THEN;
        else if (strcmp(current_token.lexeme, "else") == 0) current_token.type = TK_ELSE;
        else if (strcmp(current_token.lexeme, "while") == 0) current_token.type = TK_WHILE;
        else if (strcmp(current_token.lexeme, "end") == 0) current_token.type = TK_END;
        else if (strcmp(current_token.lexeme, "print") == 0) current_token.type = TK_PRINT;
        else current_token.type = TK_ID;
        return;
    }

    if (isdigit(c)) {
        int len = 0;
        while (isdigit(c) || c == '.') {
            current_token.lexeme[len++] = c;
            c = fgetc(source);
        }
        ungetc(c, source);
        current_token.lexeme[len] = '\0';
        current_token.value = atof(current_token.lexeme);
        current_token.type = TK_FLOAT;
        return;
    }

    current_token.lexeme[0] = c;
    current_token.lexeme[1] = '\0';
    switch (c) {
        case '+': current_token.type = TK_PLUS; break;
        case '-': current_token.type = TK_MINUS; break;
        case '*': current_token.type = TK_MUL; break;
        case '/': current_token.type = TK_DIV; break;
        case '=': current_token.type = TK_ASSIGN; break;
        case '(': current_token.type = TK_LPAREN; break;
        case ')': current_token.type = TK_RPAREN; break;
        default: error("Unknown Character"); break;
    }
}