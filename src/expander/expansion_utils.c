#include "minishell.h"

void	join_token_and_token_prev(t_token **token)
{
	t_token	*tmp;
	printf("join_token_and_token_perv called\n");
	(*token)->prev->str = ft_strjoin_with_free(&(*token)->prev->str, &(*token)->str);
	if ((*token)->prev->str == NULL)
		error("expansion.c 7: malloc error");
	(*token)->prev->len = ft_strlen((*token)->prev->str);
	(*token)->prev->next = (*token)->next;
	(*token)->next->prev = (*token)->prev;
	printf("join_token_and_token_perv 12: str == %s\n", (*token)->prev->str);
	tmp = *token;
	//	*token =
	*token = (*token)->prev;
	free(tmp);
}

char	*strdup_before_valiable(char *tmp, char *variable_name)
{
	size_t	i;
	size_t	dif;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '$')
			dif = ft_strncmp(tmp + i + 1, variable_name, ft_strlen(variable_name));
		if (dif == 0)
			return (ft_substr(tmp, 0, i));
		i++;
	}
	return (NULL);
}

char	*expand_str(char *str)
{
	char	*expanded_value;
	char	*t_str;
	char	*variable_name;
	size_t	i;

	i = 0;
	t_str = ft_strdup(str);
	// printf("strdup : t_str = %s\n", t_str);
	while (str[i])
	{
		// printf("handle_token_in_quotes 52: i = %zu,   str[i] = %c\n", i, str[i]);
		if (str[i] == '$' && (ft_isalnum((unsigned char)(str[i + 1])) || str[i + 1] == '?'))
		{
			variable_name = ft_substr(str + i, 1, get_valiable_name_len(str + i + 1));
			// fprintf(stderr, "++++++ variable_name = %s\n", variable_name);
			// fprintf(stderr, "++++++ ? = %s\n", my_getenv(g_mshell->envlist, variable_name));
			expanded_value = ft_strdup(my_getenv(g_mshell->envlist, variable_name));
			// printf("handle_token_in_quotes 56: variable_name = %s, str[i] = %c\n",  variable_name, str[i]);
			if (expanded_value == NULL && errno == 0)
				expanded_value = ft_strdup("");
			// printf("handle_token_in_quotes 40: expanded_value = %s\n", expanded_value);
			expanded_value = ft_strjoin_with_free_no_null(strdup_before_valiable(t_str, variable_name), expanded_value);
			// printf("handle_token_in_quotes 42: expanded_value = %s\n", expanded_value);
			i += ft_strlen(variable_name);
			free(variable_name);
			free(t_str);
			t_str = ft_strjoin_with_free_no_null(expanded_value, ft_substr(str+ i + 1, 0, ft_strlen(str+ i + 1)));
			if (t_str == NULL)
				error("handle_token_in_quotes.c 84: malloc error");
			// printf("handle_token_in_quotes 54: t_str = %s, i = %zu\n", t_str, i);
			//			printf("handle_token_in_quotes 54: t_str = %s, i = %d, t_str[i] = %c\n", t_str, i, t_str[i]);
			//			continue;
		}
		i++;
	}
	//	free(str);
	//	str = t_str;
	return (t_str);
}

static t_token	*new_token(t_token_kind kind, char *p, size_t len)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		error("malloc error\n");
	token->kind = kind;
	token->str = p;
	token->len = len;
	return (token);
}
