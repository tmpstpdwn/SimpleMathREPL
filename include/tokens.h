// TOKENS_H

#define FEEDVAROP '>'

typedef enum {
  ENDOFFILE,
  NEWLINE,
  NONE,
  NUMBER,
  OPERATOR,
  BRACKET,
  FEEDVAR,
  VAR
} TokenType;

TokenType gettoken(char *buffer, int max);
int isoperator(char c);
int precedence(char c);
