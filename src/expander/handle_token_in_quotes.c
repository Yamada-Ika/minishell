#include "minishell.h"

char	*remove_quotes(t_token *token, char quote)
{
	char	*str;
	char	*tmp;
	size_t	i;
	size_t	head_index;

	head_index = 0;
	if (*(token->str) == quote)
		head_index += 1;
	str = ft_strdup("");
	i = head_index;
	while (i <= token->len)
	{
		if (token->str[i] == quote || i == token->len)
		{
			tmp = ft_substr(token->str + head_index, 0, i - head_index);
			str = strjoin_and_free_null(&str, &tmp);
			if (str == NULL)
				error(strerror(errno));
			head_index = i + 1;
		}
		i++;
	}
	return (str);
}

void	handle_token_in_quotes(t_token *token)
{
	char	*str;
	char	*tmp;

	if (token->kind == TK_WORD_IN_SINGLE_Q)
		str = remove_quotes(token, '\'');
	if (token->kind == TK_WORD_IN_DOUBLE_Q)
	{
		tmp = token->str;
		token->str = expand_str(token->str);
		token->len = ft_strlen(token->str);
		free(tmp);
		str = remove_quotes(token, '"');
	}
	free(token->str);
	token->str = str;
	token->len = ft_strlen(str);
	token->kind = TK_WORD;
}
