#include "minishell.h"

int	check_op(char *s)
{
	const char	*kw[] = {">>", "<<", "<", ">", "|", "'", "\"", "$", NULL};
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

size_t	get_word_len(char *p, t_token_kind kind, char *str)
{
	size_t	len;
	int		quote_count;
	bool		is_dollar;

	len = 0;
	quote_count = 0;
	is_dollar = false;
	while (kind != TK_WORD || !ft_strchr(str, p[len]))
	{
		if (kind == TK_OP_DOLLAR && p[len] == '$'
			&& (ft_isalnum(p[len + 1]) || p[len + 1] == '?'))
			is_dollar = true;
		else if (is_dollar && (!ft_isalnum(p[len]) || p[len] == '?'))
			break ;
		if (p[len] == '\'' && kind == TK_WORD_IN_SINGLE_Q)
			quote_count += 1;
		if (p[len] == '"' && kind == TK_WORD_IN_DOUBLE_Q)
			quote_count += 1;
		if (quote_count == 2)
			kind = TK_WORD;
		if (kind == TK_WORD && p[len] == '$' && ft_isalnum(p[len + 1]))
			break ;
		len++;
	}
	return (len);
}

size_t	get_env_name_len(char *str)
{
	size_t	i;

	i = 0;
	while (ft_isalnum((char) str[i]) || str[i] == '?')
		i++;
	return (i);
}

bool	is_redirect_kind(t_token_kind kind)
{
	return (kind == TK_OP_DOUBLE_GR
		|| kind == TK_OP_SINGLE_LS
		|| kind == TK_OP_LS
		|| kind == TK_OP_GR
	);
}

t_redirect_list	*_redir_lstlast(t_redirect_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
