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

int	check_op(char *s)
{
	const char	*kw[] = {">>", "<<", "<", ">", "|", NULL};
	int			i;

	i = 0;
	while (kw[i] != NULL)
	{
		if (!ft_strncmp(s, kw[i], ft_strlen(kw[i])))
			return (i);
		i++;
	}
	return (-1);
}
