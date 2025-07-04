#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "tokens.h"
#include "stack.h"

#define INBUFFLEN 100

#define PROMPT " $ "
#define RES " = "

int main() {

    // buffer for token.
    char buffer[INBUFFLEN];

    // 26 [a-z] single letter variable storage.
    double vars[26] = {0};

    // declare variables.
    int brackets, feedvar, error;

    // Token type.
    TokenType type;
    TokenType lasttype = NONE;

    // title.
    printf("\n SimpleMathREPL [Ctrl+D to exit]\n --------------\n\n");

    // PROMPT.
    printf(PROMPT);
    fflush(stdout);

    while ((type = gettoken(buffer, INBUFFLEN)) != ENDOFFILE) {

        if (type == NUMBER) {

            // Push number to numstack.
            pushnum(atof(buffer));

        } else if (type == OPERATOR) {

            // Finish calculations with higher precedence.
            while (!opstackempty() && numcount() >= 2 &&
                   precedence(lastop()) >= precedence(buffer[0])) {
                eval();
            }

            // Push operator to opstack.
            pushop(buffer[0]);

        } else if (type == BRACKET) {

            // Push '(' to opstack.
            if (buffer[0] == '(') {
                brackets++;
                if (lasttype == NUMBER) {
                    pushop('*');
                }
                pushop(buffer[0]);

            // Finish calculations till '('.
            } else {
                brackets--;
                while (!opstackempty() && numcount() >= 2 && lastop() != '(') {
                    eval();
                }
                popop();
            }

        } else if (type == FEEDVAR) {

            // Should the output be fed into a variable?
            feedvar = 1;

        } else if (type == VAR) {

            // Fetch value stored in variable.
            pushnum(vars[buffer[0] - 'a']);

        } else if (type == NEWLINE) {

            // Are brackets balanced?
            if (brackets && !error) {
                printf(RES);
                printf("Error: Brackets not balanced!\n\n");
                error = 1;
            }

            // Finish remaining calculations.
            while (!opstackempty() && numcount() >= 2)
                eval();

            // Print result.
            if (!error) {
                printf(RES);
                printf("%f\n\n", popnum());
            }

            // Reset variables.
            brackets = 0, feedvar = 0, error = 0;
            lasttype = type;

            // Reset stack pointers.
            resetnumstack();
            resetopstack();

            // Prompt.
            printf(PROMPT);
            fflush(stdout);

        } else {

            // Print error and exit.
            printf(" = Error in input! ");
            break;

        } 
    }

    printf("OVER. \n\n");

    return 0;
}
