#include "minishell.h"

bool	can_c_be_env_name(char c)
{
	return (ft_isalnum(c) || c == '_');
}

size_t	get_env_name_len(char *str)
{
	size_t	i;

	i = 0;
	if (*str == '?')
		return (1);
	while (str[i])
	{
		if (can_c_be_env_name(str[i]) == false)
			return (i);
		i++;
	}
	return (i);
}

bool	is_env_name(char *str)
{
	if (*str != '$')
		return (false);
	if (str[1] == '?' || can_c_be_env_name(str[1]))
		return (true);
	return (false);
}

size_t	get_word_len(char *p, t_token_kind kind, char *str)
{
	size_t	len;
	int		quote_count;

	len = 0;
	quote_count = 0;
	while (kind != TK_WORD || !ft_strchr(str, p[len]))
	{
		if (kind == TK_WORD && is_env_name(p + len))
			break ;
		if (kind == TK_OP_DOLLAR && is_env_name(p + len))
			return (len + 1 + get_env_name_len(p + len + 1));
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

bool	is_redirect_kind(t_token_kind kind)
{
	return (kind == TK_OP_DOUBLE_GR
		|| kind == TK_OP_SINGLE_LS
		|| kind == TK_OP_LS
		|| kind == TK_OP_GR
	);
}
