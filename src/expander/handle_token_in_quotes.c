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
			str = ft_strjoin_with_free(&str, &tmp);
			if (str == NULL)
				error("handle_token_in_quotes: malloc error");
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

	printf("remove_quotes: %s len %zu\n", token->str, token->len);
	if (token->kind == TK_WORD_IN_SINGLE_Q)
		str = remove_quotes(token, '\'');
	if (token->kind == TK_WORD_IN_DOUBLE_Q)
	{
		str = remove_quotes(token, '"');
		tmp = str;
		printf("remove_quotes 89 : %s\n", str);
		str = expand_str(str);
		free(tmp);
	}
	printf("remove_quotes 91 : %s\n", str);
	free(token->str);
	token->str = str;
	token->len = ft_strlen(str);
	token->kind = TK_WORD;
}
