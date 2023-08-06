#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

int find_matching_paren(struct token *tokens, int n, int i) {
  int depth = 0;
  while (i < n) {
    if (tokens[i].type == LPAREN) {
      depth++;
    } else if (tokens[i].type == RPAREN) {
      depth--;
    }
    if (depth == 0) {
      return i;
    }
    i++;
  }
  return -1;
}

int is_number(char *value) {
  int i = 0;
  if (value[0] == '-') {
    i++;
  }

  while (value[i] != '\0') {
    if (value[i] < '0' || value[i] > '9') {
      return 0;
    }
    i++;
  }
  return 1;
}

int is_float(char *value) {
  int i = 0;
  if (value[0] == '-') {
    i++;
  }

  int dot = 0;
  while (value[i] != '\0') {
    if (value[i] == '.') {
      dot++;
    } else if (value[i] < '0' || value[i] > '9') {
      return 0;
    }
    i++;
  }
  return dot == 1;
}

int is_integer(char *value) { return is_number(value) && !is_float(value); }

void add_atom_child(struct expression *e, char *value) {
  if (is_integer(value)) {
    e->n++;
    e->children = realloc(e->children, sizeof(struct expression) * e->n);
    e->children[e->n - 1].type = INTEGER;
    e->children[e->n - 1].integer = atoi(value);
    e->children[e->n - 1].children = NULL;
    e->children[e->n - 1].n = 0;
    return;
  } else if (is_float(value)) {
    e->n++;
    e->children = realloc(e->children, sizeof(struct expression) * e->n);
    e->children[e->n - 1].type = FLOAT;
    e->children[e->n - 1].floating = atoi(value);
    e->children[e->n - 1].children = NULL;
    e->children[e->n - 1].n = 0;
    return;
  } else {
    e->n++;
    e->children = realloc(e->children, sizeof(struct expression) * e->n);
    e->children[e->n - 1].type = SYMBOL;
    e->children[e->n - 1].sym = value;
    e->children[e->n - 1].children = NULL;
    e->children[e->n - 1].n = 0;
  }
}

void add_subexpression_child(struct expression *e, struct expression *child) {
  e->n++;
  e->children = realloc(e->children, sizeof(struct expression) * e->n);
  e->children[e->n - 1] = *child;
}

struct expression *lookup(struct environment *env, char *symbol) {
  while (env->symbol != NULL) {
    if (strcmp(env->symbol, symbol) == 0) {
      return env->value;
    }
    env = env->next;
  }
  return NULL;
}

struct expression *new_float(float f) {
  struct expression *out = malloc(sizeof(struct expression));
  out->type = FLOAT;
  out->floating = f;
  return out;
}

struct expression *new_integer(int i) {
  struct expression *out = malloc(sizeof(struct expression));
  out->type = INTEGER;
  out->integer = i;
  return out;
}

struct expression *new_boolean(bool b) {
  struct expression *out = malloc(sizeof(struct expression));
  out->type = BOOLEAN;
  out->boolean = b;
  return out;
}
