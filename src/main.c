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

    // title.
    printf("\n SimpleMathREPL [Ctrl+D/Z to exit]\n --------------\n\n");

    while ((type = gettoken(buffer, INBUFFLEN)) != ENDOFFILE) {
        if (type == NUMBER || type == OPERATOR) {
            printf("%s\n", buffer);
        }
    }

    return 0;
}
