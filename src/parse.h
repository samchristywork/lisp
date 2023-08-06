struct token *tokenize(char *program, int *n);

struct expression *read_from_tokens(struct token *tokens, int n);

struct expression *parse(char *program);
