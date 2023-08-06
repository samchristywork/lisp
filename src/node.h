#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

enum token_type { LPAREN, RPAREN, ATOM };
enum expression_type { SYMBOL, INTEGER, FLOAT, LIST, BOOLEAN, STRING };

struct token {
  int type;
  char *value;
};

struct expression {
  int type;
  struct {
    int integer;
    float floating;
    char *sym;
    bool boolean;
  };
  struct expression *children;
  int n;
};

struct environment {
  char *symbol;
  struct expression *value;
  struct environment *next;
};

#endif
