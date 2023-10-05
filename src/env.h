#ifndef ENV_H
#define ENV_H

#include "node.h"

void add_binding(struct environment **env, char *symbol,
                 struct expression *value);

void add_float_binding(struct environment **env, char *symbol, float value);

void add_function_binding(struct environment **env, char *symbol,
                          struct expression *(*function)(struct expression *,
                                                         struct environment *));

struct environment *standard_env();

#endif
