#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "util.h"

struct token *tokenize(char *program, int *n) {
  int i = 0;
  int j = 0;
  int len = strlen(program);
  struct token *tokens = malloc(sizeof(struct token) * len);
  while (i < len) {
    if (program[i] == ';') {
      while (program[i] != '\n') {
        i++;
      }
    } else if (program[i] == '(') {
      tokens[j].type = LPAREN;
      tokens[j].value = "(";
      j++;
      i++;
    } else if (program[i] == ')') {
      tokens[j].type = RPAREN;
      tokens[j].value = ")";
      j++;
      i++;
    } else if (program[i] == ' ' || program[i] == '\n') {
      i++;
    } else {
      int k = i;
      while (program[k] != ' ' && program[k] != '\n' && program[k] != '(' &&
             program[k] != ')') {
        k++;
      }
      int length = k - i;
      char *value = malloc(sizeof(char) * length);
      strncpy(value, program + i, length);
      tokens[j].type = ATOM;
      tokens[j].value = value;
      j++;
      i = k;
    }
  }

  *n = j;
  return tokens;
}

struct expression *read_from_tokens(struct token *tokens, int n) {
  struct expression *e = malloc(sizeof(struct expression));
  e->type = LIST;
  e->n = 0;
  e->children = NULL;

  for (int i = 0; i < n;) {
    if (tokens[i].type == ATOM) {
      add_atom_child(e, tokens[i].value);
      i++;
    } else if (tokens[i].type == RPAREN) {
      printf("ERROR: unmatched RPAREN\n");
      break;
    } else if (tokens[i].type == LPAREN) {
      int rparen = find_matching_paren(tokens, n, i);
      if (rparen == -1) {
        printf("ERROR: unmatched LPAREN\n");
        break;
      }

      struct expression *subexpression =
          read_from_tokens(tokens + i + 1, rparen - i - 1);
      add_subexpression_child(e, subexpression);
      i = rparen + 1;
    } else {
      printf("UNKNOWN: %s\n", tokens[i].value);
      break;
    }
  }

  return e;
}

struct expression *parse(char *program) {
  int n = 0;
  struct token *tokens = tokenize(program, &n);

  struct expression *e = read_from_tokens(tokens, n);
  return e;
}
