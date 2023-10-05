#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

enum token_type { LPAREN, RPAREN, ATOM };

enum expression_type {
  BOOLEAN,
  FLOAT,
  FUNCTION,
  INTEGER,
  LIST,
  STRING,
  SYMBOL
};

struct token {
  int type;
  char *value;
};

struct environment {
  char *symbol;
  struct expression *value;
  struct environment *next;
};

struct expression {
  int type;
  struct {
    int integer;
    float floating;
    char *sym;
    bool boolean;
    struct expression *(*function)(struct expression *, struct environment *);
  };
  struct expression *children;
  int n;
};

#endif
