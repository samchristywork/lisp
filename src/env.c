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

struct environment *standard_env() {
  struct environment *env = malloc(sizeof(struct environment));
  add_float_binding(&env, "pi", 3.14159);
  add_float_binding(&env, "e", 2.71828);
  add_float_binding(&env, "phi", 1.61803);

  return env;
}
