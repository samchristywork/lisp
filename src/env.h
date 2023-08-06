#ifndef ENV_H
#define ENV_H

#include "node.h"

void add_binding(struct environment **env, char *symbol,
                 struct expression *value);

void add_float_binding(struct environment **env, char *symbol, float value);

struct environment *standard_env();

#endif
