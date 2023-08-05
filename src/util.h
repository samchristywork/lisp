#include "print.h"

int find_matching_paren(struct token *tokens, int n, int i);

int is_number(char *value);

int is_float(char *value);

int is_integer(char *value);

void add_atom_child(struct expression *e, char *value);

void add_subexpression_child(struct expression *e, struct expression *child);
