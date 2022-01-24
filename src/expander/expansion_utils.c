#include "minishell.h"

void	join_token_and_token_prev(t_token **token)
{
	t_token	*tmp;

	printf("join_token_and_token_perv called\n");
	(*token)->prev->str = strjoin_and_free_null
		(&(*token)->prev->str, &(*token)->str);
	if ((*token)->prev->str == NULL)
		error("expansion.c 7: malloc error");
	(*token)->prev->len = ft_strlen((*token)->prev->str);
	(*token)->prev->next = (*token)->next;
	(*token)->next->prev = (*token)->prev;
	printf("join_token_and_token_perv 12: str == %s\n", (*token)->prev->str);
	tmp = *token;
	*token = (*token)->prev;
	free(tmp);
}

char	*strdup_before_valiable(char *tmp, char *variable_name)
{
	size_t	i;
	size_t	dif;
	size_t	variable_name_len;

	i = 0;
	variable_name_len = ft_strlen(variable_name);
	while (tmp[i])
	{
		if (tmp[i] == '$')
			dif = ft_strncmp(tmp + i + 1, variable_name, variable_name_len);
		if (dif == 0)
			return (ft_substr(tmp, 0, i));
		i++;
	}
	return (NULL);
}

char	*expand_str(char *str)
{
	char	*env_val;
	char	*t_str;
	char	*env_name;
	size_t	i;

	i = 0;
	t_str = ft_strdup(str);
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalnum((str[i + 1])) || str[i + 1] == '?'))
		{
			env_name = ft_substr(str + i, 1, get_env_name_len(str + i + 1));
			errno = ERRNO_INIT_VAL;
			env_val = ft_strdup(my_getenv(g_mshell->envlist, env_name));
			if (env_val == NULL && errno == ERRNO_INIT_VAL)
				env_val = ft_strdup("");
			env_val = strjoin_and_free(strdup_before_valiable(t_str, env_name), env_val);
			i += ft_strlen(env_name);
			ft_free((void **)&env_name, (void **)&t_str);
			t_str = strjoin_and_free(env_val, ft_strdup(str + i + 1));
			if (t_str == NULL)
				error("handle_token_in_quotes.c 84: malloc error");
		}
		i++;
	}
	return (t_str);
}

size_t	join_valiable(char **p, t_token **tok)
{
	t_token	*cur;
	t_token	head;
	size_t	count;

	count = 0;
	head.next = NULL;
	cur = &head;
	while (p[count])
	{
		cur->next = new_token_tk_word(TK_WORD, p[count], ft_strlen(p[count]));
		cur->next->prev = cur;
		cur = cur->next;
		count++;
	}
	free(p);
	cur->next = (*tok)->next;
	cur->next->prev = cur;
	(*tok)->prev->next = head.next;
	head.next->prev = (*tok)->prev;
	free((*tok)->str);
	free(*tok);
	*tok = cur;
	return (count);
}

t_token	*new_token_tk_word(t_token_kind kind, char *p, size_t len)
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
