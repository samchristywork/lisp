#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "node.h"

void add_binding(struct environment **env, char *symbol,
                 struct expression *value) {
  struct environment *new_env = malloc(sizeof(struct environment));
  new_env->symbol = symbol;
  new_env->value = value;
  new_env->next = *env;

  *env = new_env;
}

void add_float_binding(struct environment **env, char *symbol, float value) {
  struct expression *var = malloc(sizeof(struct expression));
  var->type = FLOAT;
  var->floating = value;
  add_binding(env, symbol, var);
}

void add_function_binding(
    struct environment **env, char *symbol,
    struct expression *(*function)(struct expression *, struct environment *)) {
  struct expression *var = malloc(sizeof(struct expression));
  var->type = FUNCTION;
  var->function = function;
  add_binding(env, symbol, var);
}

struct expression *eval_sin(struct expression *arg, struct environment *env) {
  struct expression *result = malloc(sizeof(struct expression));
  result->type = FLOAT;
  result->floating = sin(arg->children[1].floating);
  return result;
}

struct expression *undefined(struct expression *arg, struct environment *env) {
  printf("Undefined function\n");
  return NULL;
}

struct environment *standard_env() {
  struct environment *env = malloc(sizeof(struct environment));
  add_float_binding(&env, "pi", 3.14159);
  add_float_binding(&env, "e", 2.71828);
  add_float_binding(&env, "phi", 1.61803);

  return env;
}
