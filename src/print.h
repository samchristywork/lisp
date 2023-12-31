#ifndef PRINT_H
#define PRINT_H

void print_tokens(struct token *tokens, int n);

void print_expression(struct expression *e);

void print_tree(struct expression *e, int depth);

void print_env(struct environment *env);

#endif
