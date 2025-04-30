// INCLUDES

#include <stdio.h>
#include <ctype.h>
#include "utils.h"
#include "stack.h"
#include "helpers.h"

// MAIN

int main() {

    // buffer for line.
    char line[INBUFFLEN];

    // 26 [a-z] single letter variable storage for doubles.
    double vars[26] = {0};

    // declare variables.
    int lastread, brackets, feedvar, error, len, i;

    // title.
    printf("\n SimpleMathREPL [Ctrl+D/Z to exit]\n --------------\n\n");

    // print PROMPT.
    printf(PROMPT);
    fflush(stdout);

    while ((len = readline(line, INBUFFLEN)) >= 0) {

        // skip iteration if input is empty.
        if (!len || isfullwhitespace(line)) {
            // print PROMPT.
            printf(PROMPT);
            fflush(stdout);
            continue;
        }

        // reset variables.
        i = 0;
        error = 0;
        feedvar = 0;
        brackets = 0;
        lastread = NONE;

        // until line is finished.
        while (line[i] != '\0') {

            // push number.
            if (isnumber(line, i)) {
                if (lastread == NUM) {
                    printf(PROMPT);
                    printf("Error: Expected an operator after %f!\n\n", lastnum());
                    error = 1;
                    break;
                }
                pushnum(getnum(line, &i));
                lastread = NUM;

            // push operator and eval previous entries based on precedence.
            } else if (isoperator(line[i])) {
                if (lastread != NUM) {
                    printf(PROMPT);
                    printf("Error: Expected a number before \'%c\'!\n\n", line[i]);
                    error = 1;
                    break;
                }
                while (!opstackempty() && numcount() >= 2 &&
                        precedence(lastop()) >= precedence(line[i])) {
                    eval();
                }
                pushop(line[i]);
                lastread = OP;
                i++;

            // push '('.
            } else if (line[i] == '(') {
                brackets++;
                pushop(line[i]);
                i++;

            // eval previous entries if ')' is met, till '(' or break.
            } else if (line[i] == ')') {
                brackets--;

                while (!opstackempty() && numcount() >= 2 && lastop() != '(') {
                    eval();
                }

                if (lastop() != '(')
                    break;

                popop();
                i++;

            // set feedvar to 1 and break the loop.
            } else if (line[i] == '>') {
                if (lastread != NUM) {
                    printf(PROMPT);
                    printf("Error: Expected a valid expression / number before \'>\' operator!\n\n");
                    error = 1;
                    break;
                }
                feedvar = 1;
                i++;
                break;

            // read from a variable.
            } else if (islower(line[i])){
                if (lastread == NUM) {
                    printf(PROMPT);
                    printf("Error: Expected an operator before \'%c\' variable!\n\n", line[i]);
                    error = 1;
                    break;
                } else if (!isspace(line[i+1]) && line[i+1] != '\0') {
                    printf(PROMPT);
                    printf("Error: Invalid variable name!\n\n");
                    error = 1;
                    break;
                }
                pushnum(vars[line[i] - 'a']);
                lastread = NUM;
                i++;

            } else {
                i++;

            }
        }

        // check for unbalanced brackets.
        if (brackets && !error) {
            printf(PROMPT);
            printf("Error: Brackets not balanced!\n\n");
            error = 1;
        }

        // eval remaining entries.
        while (!opstackempty() && numcount() >= 2)
            eval();
        if (!opstackempty() && !error) {
            printf(PROMPT);
            printf("Error: Excess operators found!\n\n");
            error = 1;
        }

        // feed result to a variable [a-z] if need to.
        if (feedvar && !error) {
            while (line[i] != '\0' && !islower(line[i])) i++;
            if (islower(line[i])) {
                char var = line[i];
                i++;
                while (isspace(line[i]) && line[i] != '\0') i++;
                if (line[i] != '\0') {
                    printf(PROMPT);
                    printf("Error: Expected a variable name [a-z]!\n\n");
                    error = 1;
                } else {
                    vars[var - 'a'] = lastnum();
                }
            } else {
                printf(PROMPT);
                printf("Error: Expected a variable name [a-z]!\n\n");
                error = 1;
            }
        }

        // print result if there are no errors.
        if (!error) {
            printf(RESSYM);
            printf("%f\n\n", popnum());
        }

        // reset both stack pointers.
        resetnumstack();
        resetopstack();

        // print PROMPT.
        printf(PROMPT);
        fflush(stdout);
    }

    // newline after exit and return 0.
    printf("\n\n");
    return 0;
}

// END
