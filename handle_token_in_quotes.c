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

char	*valiable_expansion_in_quote(char *str)
{
	char	*t_str;
	char	*tmp;
	char	*variable_name;
	size_t	i;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		printf("handle_token_in_quotes 52: i = %zu,   str[i] = %c\n", i, str[i]);
		if (str[i] == '$' && ft_isalnum((unsigned char)(str[i + 1])))
		{
			variable_name = ft_substr(str + i, 1, get_valiable_name_len(str + i + 1));
			t_str = ft_strdup(getenv(variable_name));
			printf("handle_token_in_quotes 56: variable_name = %s, str[i] = %c\n", variable_name, str[i]);
			if (t_str == NULL && errno == 0)
				t_str = ft_strdup("");
			t_str = ft_strjoin_with_free_no_null(ft_substr(str, 0, i), t_str);
			i += ft_strlen(variable_name);
			printf("handle_token_in_quotes 54: t_str = %s\n", t_str);
			free(tmp);
			tmp =  ft_strjoin_with_free_no_null(t_str, ft_substr(str+ i + 1, 0, ft_strlen(str+ i + 1)));
			if (tmp == NULL)
				error("handle_token_in_quotes.c: malloc error");
			printf("handle_token_in_quotes 54: tmp = %s, i = %d\n", tmp, i);
//			printf("handle_token_in_quotes 54: tmp = %s, i = %d, tmp[i] = %c\n", tmp, i, tmp[i]);
//			continue;
		}
		i++;
	}
	str = tmp;
	return (str);

}


void	handle_token_in_quotes(t_token *token)
{
	char *str;

	printf("remove_quotes: %.*s len %zu\n",token->len,  token->str, token->len);
	if (token->kind == TK_WORD_IN_SINGLE_Q)
		str = remove_quotes(token, '\'');
	if (token->kind == TK_WORD_IN_DOUBLE_Q)
		str = remove_quotes(token, '"');
	printf("remove_quotes 45 : %s\n", str);
	str = valiable_expansion_in_quote(str);
	token->str = str;
	token->len = ft_strlen(str);
}
