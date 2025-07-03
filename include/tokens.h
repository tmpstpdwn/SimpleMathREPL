// TOKENS_H

typedef enum {
  ENDOFFILE,
  NONE,
  NUMBER,
  OPERATOR
} TokenType;

TokenType gettoken(char *buffer, int max);
int isoperator(char c);
int precedence(char c);
