#include "minishell.h"

void	skip_space(char **s)
{
	while (**s == ' ')
		(*s)++;
}

bool	is_quote_closed(char c, t_token_kind kind)
{
	if (c == '"' && kind == TK_WORD_IN_DOUBLE_Q)
		return (true);
	if (c == '\'' && kind == TK_WORD_IN_SINGLE_Q)
		return (true);
	return (false);
}
