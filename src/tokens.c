#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "tokens.h"

// lastread token.
static TokenType lastread = NONE;

// Tokeniser.
TokenType gettoken(char *buffer, int max) {
    int c;
    *buffer = '\0';

    while (isspace(c = getchar()));
    
    if (c == EOF) {
        return ENDOFFILE;
    }

    *buffer++ = c;

    if (!isdigit(c)) {
        *buffer = '\0';
        if (isoperator(c)) {
            return OPERATOR;
        }
        return NONE;
    }

    for (int i = 0; isdigit(c = getchar()) && i < max - 1; i++) {
        *buffer++ = c;
    }

    if (c != EOF) {
        ungetc(c, stdin);
    }

    *buffer = '\0';

    return NUMBER;
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
