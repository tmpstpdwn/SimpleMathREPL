// INCLUDES
#include <stdio.h>
#include <ctype.h>
#include "utils.h"

// MAIN
int main() {

    // buffer for line.
    char line[LEN];

    // 26 [a-z] single letter variable storage for doubles.
    double vars[26] = {0};

    // declare variables.
    int lastread, feedvar, len, i;

    // title.
    printf("\n SimpleMathREPL [Ctrl+D/Z to exit]\n --------------\n\n");

    // print PROMPT.
    printf(PROMPT);
    fflush(stdout);

    while ((len = readline(line, LEN)) >= 0) {

        // skip iteration if input is empty.
        if (!len || isfullwhitespace(line)) {
            // print PROMPT.
            printf(PROMPT);
            fflush(stdout);
            continue;
        }

        // reset variables.
        i = 0;
        feedvar = 0;
        lastread = NONE;

        // until line is finished.
        while (line[i] != '\0') {

            // push number.
            if (isnumber(line, i) && lastread != NUM) {
                pushnum(getnum(line, &i));
                lastread = NUM;

            // push operator and eval previous entries based on precedence.
            } else if (isoperator(line[i]) && lastread != OP) {
                while (precedence(lastop()) >= precedence(line[i]) && eval());
                pushop(line[i]);
                lastread = OP;
                i++;

            // push '('.
            } else if (line[i] == '(') {
                pushop(line[i]);
                i++;

            // eval previous entries if ')' is met.
            } else if (line[i] == ')') {
                while (eval());
                i++;

            // set feedvar to 1 and break the loop.
            } else if (line[i] == '>') {
                feedvar = 1;
                break;
                i++;

            // read from a variable.
            } else if (islower(line[i]) && lastread != NUM){
                pushnum(vars[line[i] - 'a']);
                lastread = NUM;
                i++;

            } else {
                i++;

            }
        }

        // eval remaining entries and print result.
        while (eval());
        printf(" = %f\n\n", lastnum());

        // feed result to a variable [a-z] if need to.
        if (feedvar) {
            while (line[i] != '\0' && !islower(line[i])) i++;
            if (islower(line[i])) {
                vars[line[i] - 'a'] = popnum();
            }
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
