// INCLUDES
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "utils.h"

// DEF

// Read a line till '\n' or EOF or till buffer extinguishes and end it with '\0'.
int readline(char *line, int max) {
    int i, c;
    for (i = 0; i < max-1 && (c = getchar()) != EOF && c != '\n'; i++) {
        line[i] = c;
    }
    line[i] = '\0';
    return (c == EOF && i == 0)? -1: i;
}

// is line just empty whitespace?
int isfullwhitespace(char *line) {
    while (isspace(*line)) line++;
    if (*line == '\0')
        return 1;
    return 0;
}

// is 'c' an operator?
int isoperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// is line[i] a number or start of a number?
int isnumber(char *line, int i) {
    if (isdigit(line[i])) {
        return 1;
    }

    if ((line[i] == '-' || line[i] == '+') && (isdigit(line[i+1]) || line[i+1] == '.')) {
        return 1;
    }

    if (line[i] == '.' && isdigit(line[i+1])) {
        return 1;
    }

    return 0;
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

// get the number at line[i] or one that starts there.
double getnum(char *line, int *i) {
    char num[NUMLEN];
    int j = 0;
    int dec = 0;

    if (line[*i] == '-' || line[*i] == '+') {
        num[j++] = line[(*i)++];
    } 

    if (line[*i] == '.') {
        dec = 1;
        num[j++] = line[(*i)++];
    }

    while (isdigit(line[*i])) {
        num[j] = line[*i];
        (*i)++, j++;
    }

    if (line[*i] == '.' && !dec) {
        num[j] = line[*i];
        (*i)++, j++;
    }

    while (isdigit(line[*i])) {
        num[j] = line[*i];
        (*i)++, j++;
    }

    num[j] = '\0';
    return atof(num);
}

// END
