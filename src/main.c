#include <stdio.h>
#include <ctype.h>
#include "tokens.h"
#include "stack.h"

#define INBUFFLEN 100

int main() {

    // buffer for line.
    char buffer[INBUFFLEN];

    // 26 [a-z] single letter variable storage.
    double vars[26] = {0};

    // declare variables.
    int brackets, feedvar, error, i;

    // Token type.
    TokenType type;

    while ((type = gettoken(buffer, INBUFFLEN)) != ENDOFFILE) {
        if (type == NEWLINE) {
            continue;
        }
        printf("%s: %d\n", buffer, type);
    }

    return 0;
}
