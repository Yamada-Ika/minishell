#include "minishell.h"

t_token	*new_token_tk_word(t_token_kind kind, char *p, size_t len)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		error("malloc error");
	token->kind = kind;
	token->str = p;
	token->len = len;
	return (token);
}
