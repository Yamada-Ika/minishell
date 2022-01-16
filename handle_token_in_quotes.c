#include "minishell.h"

char	*remove_quotes(t_token *token, char quote)
{
	char	*str;
//	char	*head;
	char	*cur;
	char	*tmp;
	size_t	i;
	size_t	head_index;

	if (*(token->str) == quote)
		head_index = 1;
	else
		head_index = 0;
	cur =token->str;
	str = ft_strdup("");
	i = head_index;
//	i = *head - *(token->str);
		printf("handle_token_in_quotes.c 19: *cur %c, i %d\n", cur[i], i);
	while(i <= token->len)
	{
//		printf("handle_token_in_quotes.c 22: *cur %c\n", cur[i]);
		if (cur[i] == quote || i ==  token->len)
		{
			if (i != head_index)
			{
				tmp = ft_substr(token->str + head_index, 0, i - head_index);
				printf("handle_token_in_quotes.c 19: tmp %s, len %d\n", tmp, i - head_index);
				str = ft_strjoin_with_free(&str, &tmp);
			}
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
	char *str;

	printf("remove_quotes: %.*s len %zu\n",token->len,  token->str, token->len);
	if (token->kind == TK_WORD_IN_SINGLE_Q)
		str = remove_quotes(token, '\'');
	if (token->kind == TK_WORD_IN_DOUBLE_Q)
	{
		str = remove_quotes(token, '"');
		printf("remove_quotes 89 : %s\n", str);
		str = expand_str(str);
	}
	printf("remove_quotes 91 : %s\n", str);
	token->str = str;
	token->len = ft_strlen(str);
}
