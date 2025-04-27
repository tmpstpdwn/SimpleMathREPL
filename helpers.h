// helpers.c
int readline(char *line, int max);
int isfullwhitespace(char *line);
int isoperator(char c);
int isnumber(char *line, int i);
int precedence(char c);
double getnum(char *line, int *i);

// END
