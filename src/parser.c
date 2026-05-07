#include "../include/compiler.h"

void match(TokenType expected) {
    if (current_token.type == expected) advance();
    else error("Unexpected token");
}

double expression();

double factor() {
    double val = 0;
    if (current_token.type == TK_FLOAT) {
        val = current_token.value;
        advance();
    } else if (current_token.type == TK_ID) {
        advance(); 
    } else if (current_token.type == TK_LPAREN) {
        advance();
        val = expression();
        match(TK_RPAREN);
    }
    return val;
}

double term() {
    double left = factor();
    while (current_token.type == TK_MUL || current_token.type == TK_DIV) {
        TokenType op = current_token.type;
        advance();
        double right = factor();
        if (op == TK_MUL) left *= right;
        else if (right != 0) left /= right;
    }
    return left;
}

double expression() {
    double left = term();
    while (current_token.type == TK_PLUS || current_token.type == TK_MINUS) {
        TokenType op = current_token.type;
        advance();
        double right = term();
        if (op == TK_PLUS) left += right;
        else left -= right;
    }
    return left;
}

void statement() {
    if (current_token.type == TK_ID) {
        char name[32];
        strcpy(name, current_token.lexeme);
        advance();
        match(TK_ASSIGN);
        double val = expression();
        printf("STORE %s, %.2f\n", name, val);
    } else if (current_token.type == TK_PRINT) {
        advance();
        double val = expression();
        printf("OUT %.2f\n", val);
    } else if (current_token.type == TK_IF) {
        advance();
        expression(); 
        match(TK_THEN);
        while (current_token.type != TK_END && current_token.type != TK_EOF) statement();
        match(TK_END);
    } else {
        advance();
    }
}

void parse() {
    advance();
    while (current_token.type != TK_EOF && current_token.type != TK_ERROR) {
        statement();
    }
}