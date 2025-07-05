// TOKENS_H

#define FEEDVAROP '>'

typedef enum {
  ENDOFFILE,
  NEWLINE,
  NONE,
  NUMBER,
  OPERATOR,
  LBRACKET,
  RBRACKET,
  FEEDVAR,
  VAR
} TokenType;

void skipline();
TokenType gettoken(char *buffer, int max);
int isoperator(char c);
int precedence(char c);
