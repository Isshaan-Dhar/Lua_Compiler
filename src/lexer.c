#include "../include/compiler.h"

int line_num = 1;
Token current_token;
FILE *source = NULL;

// Fast keyword lookup using a small static table
const struct { const char* str; TokenType type; } keywords[] = {
    {"if", TK_IF}, {"else", TK_ELSE}, {"while", TK_WHILE},
    {"end", TK_END}, {"then", TK_THEN}, {"print", TK_PRINT},
    {NULL, 0}
};

void advance() {
    int c;
    while ((c = fgetc(source)) != EOF) {
        if (c == '\n') { line_num++; continue; }
        if (isspace(c)) continue;

        // Optimized Comment Skip
        if (c == '-') {
            int next = fgetc(source);
            if (next == '-') {
                while ((c = fgetc(source)) != EOF && c != '\n');
                if (c == '\n') line_num++;
                continue;
            }
            ungetc(next, source);
        }

        // Identifier/Keyword scan
        if (isalpha(c) || c == '_') {
            int len = 0;
            current_token.lexeme[len++] = c;
            while (isalnum(c = fgetc(source)) || c == '_') {
                if (len < 31) current_token.lexeme[len++] = c;
            }
            ungetc(c, source);
            current_token.lexeme[len] = '\0';
            
            current_token.type = TK_ID;
            for (int i = 0; keywords[i].str; i++) {
                if (strcmp(current_token.lexeme, keywords[i].str) == 0) {
                    current_token.type = keywords[i].type;
                    break;
                }
            }
            current_token.line = line_num;
            return;
        }

        // Fast Numeric Scan (Int and Float)
        if (isdigit(c)) {
            int len = 0;
            current_token.lexeme[len++] = c;
            bool is_float = false;
            while (isdigit(c = fgetc(source)) || c == '.') {
                if (c == '.') is_float = true;
                if (len < 31) current_token.lexeme[len++] = c;
            }
            ungetc(c, source);
            current_token.lexeme[len] = '\0';
            current_token.type = is_float ? TK_FLOAT : TK_INT;
            current_token.value = atof(current_token.lexeme);
            return;
        }

        // Single Character Operators
        current_token.lexeme[0] = c;
        current_token.lexeme[1] = '\0';
        current_token.line = line_num;
        switch(c) {
            case '+': current_token.type = TK_PLUS; return;
            case '-': current_token.type = TK_MINUS; return;
            case '*': current_token.type = TK_MUL; return;
            case '/': current_token.type = TK_DIV; return;
            case '=': current_token.type = TK_ASSIGN; return;
            case '(': current_token.type = TK_LPAREN; return;
            case ')': current_token.type = TK_RPAREN; return;
        }
    }
    current_token.type = TK_EOF;
}

void error(const char* msg) {
    fprintf(stderr, "Error at line %d: %s (Lexeme: %s)\n", line_num, msg, current_token.lexeme);
    exit(1);
}