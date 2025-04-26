// INLCUDES
#include "utils.h"

// GLOBALS
static char opstack[LEN];
static int opptr = 0;

static double numstack[LEN];
static int numptr = 0;

// DEF

// push 'c' to opstack.
void pushop(char c) {
    if (opptr < LEN) {
        opstack[opptr++] = c;
    }
}

// push 'd' to numstack.
void pushnum(double d) {
    if (numptr < LEN) {
        numstack[numptr++] = d;
    }
}

// pop from opstack.
char popop(void) {
    return (opptr > 0)? opstack[--opptr]: 0;
}

// pop from numstack.
double popnum(void) {
    return (numptr > 0)? numstack[--numptr]: 0;
}

// return last pushed to opstack without popping.
char lastop(void) {
    return (opptr > 0)? opstack[opptr - 1]: 0;
}

// return last pushed to numstack without popping.
double lastnum(void) {
    return (numptr > 0)? numstack[numptr - 1]: 0;
}

// is opstack empty>
int opstackempty(void) {
    return opptr == 0;
}

// return count of numbers in numstack;
int numcount(void) {
    return numptr;
}

// set numptr to 0.
void resetnumstack(void) {
    numptr = 0;
}

// set opptr to 0.
void resetopstack(void) {
    opptr = 0;
}

// eval stack entries, return 1 if successfull or 0 otherwise.
int eval(void) {
    if (opstackempty() || numcount() < 2) {
        return 0;
    } else if (lastop() == '(') {
        popop();
        return 0;
    }

    char op = popop();
    double num1 = popnum();
    double num2 = popnum();
    
    switch (op) {
        case '+':
            pushnum(num1 + num2);
            break;
        case '-':
            pushnum(num2 - num1);
            break;
        case '*':
            pushnum(num1 * num2);
            break;
        case '/':
            pushnum(num2 / num1);
            break;
    }
    return 1;
}

// END
