#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

void print_tokens(struct token *tokens, int n) {
  printf("%d tokens: [ ", n);
  for (int i = 0; i < n; i++) {
    printf("%s ", tokens[i].value);
  }
  printf("]\n");
}

void print_expression(struct expression *e) {
  if (e == NULL) {
    printf("NULL\n");
    return;
  }

  switch (e->type) {
  case SYMBOL:
    printf("SYMBOL");
    printf(" %s", e->sym);
    printf("\n");
    break;
  case INTEGER:
    printf("INTEGER");
    printf(" %d", e->integer);
    printf("\n");
    break;
  case FLOAT:
    printf("FLOAT");
    printf(" %f", e->floating);
    printf("\n");
    break;
  case LIST:
    printf("LIST");
    printf("\n");
    break;
  default:
    printf("UNKNOWN");
    break;
  }
}

void print_tree(struct expression *e, int depth) {
  for (int i = 0; i < depth; i++) {
    printf("  ");
  }

  print_expression(e);

  if (e->type == LIST) {
    for (int i = 0; i < e->n; i++) {
      print_tree(e->children + i, depth + 1);
    }
  }
}
