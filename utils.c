#include "minishell.h"

void error(char *str)
{
    ft_putstr_fd(str, 2);
    exit(1);
}

int	check_op(char *s)
{
	const char *kw[] = {">>", "<<", "<", ">", "|", "'", "\"", "$", NULL};
	int		i;

	i = 0;
	while (kw[i] != NULL)
	{
		if (!ft_strncmp(s, kw[i], ft_strlen(kw[i])))
			return (i);
		i++;

	}
	return (-1);
}

size_t  get_word_len(char *p, t_token_kind kind, char *str)
{
	size_t	len;
	int		quote_count;

	len = 0;
	quote_count = 0;
	while (kind != TK_WORD || !ft_strchr(str, p[len]) || (p[len] == '$' && p[len + 1] != ' '))
	{
		if (p[len] == '\'' && kind == TK_WORD_IN_SINGLE_Q)
			quote_count += 1;
		if (p[len] == '"' && kind == TK_WORD_IN_DOUBLE_Q)
			quote_count += 1;
		if (quote_count == 2)
			kind = TK_WORD;
		len++;
	}
	return (len);
}
