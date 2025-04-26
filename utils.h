// #DEFINES
#define LEN 100
#define PROMPT " > "

// ENUMS
enum {NONE, OP, NUM};

// helpers.c
int readline(char *line, int max);
int isfullwhitespace(char *line);
int isoperator(char c);
int isnumber(char *line, int i);
int precedence(char c);
double getnum(char *line, int *i);

// stack.c
void pushop(char c);
void pushnum(double d);
char popop(void);
double popnum(void);
char lastop(void);
double lastnum(void);
int opstackempty(void);
int numcount(void);
void resetnumstack(void);
void resetopstack(void);
int eval(void);

// END
