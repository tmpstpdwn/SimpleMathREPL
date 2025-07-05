#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "tokens.h"
#include "stack.h"

// Size for each token.
#define INBUFFLEN 100

// Config appearance.
#define PROMPT " $ "
#define RES " = "

// Main.
int main() {

    // buffer for token.
    char buffer[INBUFFLEN];

    // 26 [a-z] single letter variable storage.
    double vars[26] = {0};

    // declare variables.
    int brackets = 0;
    int feedvar = 0;
    int var;
    int error = 0;

    // Token type.
    TokenType type;
    TokenType lastype = NONE;

    // title.
    printf("\n SimpleMathREPL [Ctrl+D to exit]\n --------------\n\n");

    // PROMPT.
    printf(PROMPT);
    fflush(stdout);

    while ((type = gettoken(buffer, INBUFFLEN)) != ENDOFFILE) {

        if (lastype == NEWLINE) {

            // Reset variables.
            brackets = 0;
            feedvar = 0;
            error = 0;
        }

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

        } else if (type == LBRACKET) {

            // Push '(' to opstack.
            brackets++;
            pushop(buffer[0]);

        } else if (type == RBRACKET){

            // Finish calculations till '('.
            brackets--;
            while (!opstackempty() && numcount() >= 2 && lastop() != '(') {
                eval();
            }
            popop();
            
        } else if (type == VAR) {

            // Push value stored in variable.
            pushnum(vars[buffer[0] - 'a']);

        } else if (type == FEEDVAR) {

            // Should the output be fed into a variable?
            TokenType temp;
            if ((temp = gettoken(buffer, INBUFFLEN)) == VAR) {
                feedvar = 1;
                var = buffer[0] - 'a';
            } else {
                printf(RES);
                printf("Error: Wrong variable assignation!\n\n");
                error = 1;
            }

            if (temp != NEWLINE) {
                skipline();
            }

            type = NEWLINE;

        } else if (type == NONE) {

            // Error in case of un-indentified tokens.
            printf(RES);
            printf("Error: Invalid input!\n\n");
            skipline();
            error = 1;
            type = NEWLINE;
        }

        if (type == NEWLINE) {

            // Are brackets balanced?
            if (brackets && !error) {
                printf(RES);
                printf("Error: Brackets not balanced!\n\n");
                error = 1;
            }

            // Finish remaining calculations.
            if (!error) {
                while (!opstackempty() && numcount() >= 2) {
                    eval();
                }
                if (!opstackempty() || numcount() >= 2) {
                    printf(RES);
                    printf("Error: Invalid input!\n\n");
                    error = 1;
                }
            }

            // Feed a variable.
            if (feedvar && !error) {
                vars[var] = lastnum();
            }

            // Print result.
            if (!error) {
                printf(RES);
                printf("%f\n\n", popnum());
            }

            // Reset stack pointers.
            resetnumstack();
            resetopstack();

            // Prompt.
            printf(PROMPT);
            fflush(stdout);

        }

        // Last token type.
        lastype = type;
    }

    printf("OVER. \n\n");

    return 0;
}
