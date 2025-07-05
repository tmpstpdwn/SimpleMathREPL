#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "tokens.h"

// lastread token.
static TokenType lastread = NONE;

// Skip the current line.
void skipline() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Tokenizer.
TokenType gettoken(char buffer[], int max) {
    int c;
    int i = 0;
    int decimals = 0;
    buffer[i] = '\0';

    while ((c = getchar()) == ' ' || c == '\t');

    if (c == '\n') {
        return (lastread = NEWLINE);
    }

    if (c == EOF) {
        return ENDOFFILE;
    }

    buffer[i++] = c;

    decimals = (c == '.')? 1: 0;

    if (!isdigit(c) && c != '.') {
        buffer[i] = '\0';
        if (isoperator(c)) {
            int isanoperator = lastread == NUMBER || lastread == VAR || lastread == RBRACKET;
            if (isanoperator) {
                return (lastread = OPERATOR);
            }
        } else if (islower(c)){
            return (lastread = VAR);
        } else if (c == '(') {
            return (lastread = LBRACKET);
        } else if (c == ')') {
            return (lastread = RBRACKET);
        } else if (c == FEEDVAROP) {
            return (lastread = FEEDVAR);
        } else {
            return (lastread = NONE);
        }
    }

    if (isoperator(c)) {
        if (c != '+' && c != '-') {
            return NONE;
        }
        c = getchar();
        if (c == '.' && i < max - 1) {
            buffer[i++] = c;
            decimals = 1;
        } else {
            ungetc(c, stdin);
        }
    }

    while (isdigit(c = getchar()) && i < max - 1) {
        buffer[i++] = c;
    }

    if (c == '.' && i < max - 1 && !decimals) {
        buffer[i++] = c;
    } else {
        ungetc(c, stdin);
    }

    while (isdigit(c = getchar()) && i < max - 1) {
        buffer[i++] = c;
    }

    if (c != EOF) {
        ungetc(c, stdin);
    }

    buffer[i] = '\0';
    if ((isoperator(buffer[0]) && strlen(buffer) == 1) || buffer[i-1] == '.') {
        return (lastread = NONE);
    }
    return (lastread = NUMBER);
}

// is 'c' an operator?
int isoperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// return precedence of 'c'.
int precedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/' ) {
        return 2;
    } else {
        return 0;
    }
}
