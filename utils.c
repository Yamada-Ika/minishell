#include "minishell.h"

void error(char *str)
{
    ft_putstr_fd(str, 2);
    exit(1);
}

int	check_op(char *s)
{
	const char *kw[] = {"<<", ">>", "<", ">", "|", "'", "\"", "$", NULL};
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

size_t  get_word_len(char *p, char *str)
{
	size_t  len;

	len = 0;
	while (!ft_strchr(str, p[len]) || (p[len] == '$' && p[len + 1] != ' '))
		len++;
	return (len);
}
