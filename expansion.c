#include "minishell.h"

void	join_token_and_token_prev(t_token **token)
{
	printf("join_token_and_token_perv called\n");
	(*token)->str = ft_strjoin_with_free(&(*token)->prev->str, &(*token)->str);
	if ((*token)->str == NULL)
		error("expansion.c 7: malloc error");
	(*token)->len = ft_strlen((*token)->str);
	(*token)->prev->prev->next = *token;
	(*token)->prev = (*token)->prev->prev;
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
	char	*t_str;
	char	*tmp;
	char	*variable_name;
	size_t	i;

	i = 0;
	tmp = ft_strdup(str);
	printf("strdup : tmp = %s\n", tmp);
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
			printf("handle_token_in_quotes 40: t_str = %s\n", t_str);
			t_str = ft_strjoin_with_free_no_null(strdup_before_valiable(tmp, variable_name), t_str);
			printf("handle_token_in_quotes 42: t_str = %s\n", t_str);
			i += ft_strlen(variable_name);
			free(tmp);
			tmp =  ft_strjoin_with_free_no_null(t_str, ft_substr(str+ i + 1, 0, ft_strlen(str+ i + 1)));
			if (tmp == NULL)
				error("handle_token_in_quotes.c 84: malloc error");
			printf("handle_token_in_quotes 54: tmp = %s, i = %d\n", tmp, i);
//			printf("handle_token_in_quotes 54: tmp = %s, i = %d, tmp[i] = %c\n", tmp, i, tmp[i]);
//			continue;
		}
		i++;
	}
//	if (tmp != NULL)
		str = tmp;
	return (str);
	
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

static size_t	join_valiable(char **p, t_token **tok)
{
	t_token	*cur;
	t_token	head;
	size_t	count;

	count = 0;
	head.next = NULL;
	cur = &head;
	while (p[count])
	{
		cur->next = new_token(TK_EXP_WORD, p[count], ft_strlen(p[count]));
		cur->next->prev = cur;
		cur = cur->next;
		count++;
		printf("expansion.c 88: count %zu\n", count);
	}
	cur->next = (*tok)->next;
	printf("expansion.c 91: tok-next-str %s\n",  (*tok)->next->str);
	cur->next->prev = cur;
	(*tok)->prev->next = head.next;
	head.next->prev = (*tok)->prev;
	*tok = cur;
	fprintf(stderr, "count : %lld\n", count);
	return (count);
}

static void debug_token(t_token *token, size_t loop_cnt)
{
	const char *kind[] = {
		"TK_OP_DOUBLE_GR",
		"TK_OP_SINGLE_LS",
		"TK_OP_LS",
		"TK_OP_GR",
		"TK_OP_PIPE",
		"TK_OP_DOLLAR",
		"TK_WORD",
		"TK_WORD_IN_SINGLE_Q",
		"TK_WORD_IN_DOUBLE_Q",
		"TK_EOF",
	};
	size_t	i;

	i = 0;
	while (i < loop_cnt)
	{
		if (token == NULL)
		{
			i++;
			continue ;
		}
		printf("{kind:%s, str:%.*s, prev->kind:%s, prev->str:%.*s}\n", 
			kind[token->kind],
			token->len,
			token->str,
			kind[token->prev->kind],
			token->prev->len,
			token->prev->str
			);
		token = token->next;
		i++;
	}
}

 size_t	replace_token(t_token **token, char *str)
 {
 	t_token	*head;
 	size_t	increase_tok_num;
	char	**strs;

 	head = *token;
 	if (*str == '\0')
 	{
 		(*token)->prev->next = (*token)->next;
 		(*token)->next->prev = head->prev;
 		*token = head->next;
		free(head);
 		free(str);
 		return (0);
 	}
	 strs = ft_split(str, ' ');
 	if (strs == NULL)
		 error("expansion.c 153: malloc error");
 	increase_tok_num = join_valiable(strs, token);
 	debug_token(head, 1);
 	free(head);

 	return (increase_tok_num);
 }

 size_t	expand_token(t_token **token, int op_kind)
 {
 	char	*str;
 	char	*variable_name;

 	 fprintf(stderr,"expand_token called\n");
 	if (op_kind == TK_OP_DOLLAR)
 	{
 		str = expand_str((*token)->str);
		 fprintf(stderr,"expand_token 173:  %s\n", str);
		 fprintf(stderr,"expand_token 174:  %s\n", (*token)->next->str);
 		if (errno)
 			error(strerror(errno));
 		if (str != NULL)
 			fprintf(stderr, "%s\n", str);
 		return (replace_token(token, str));
 	}
 	return (0);
 }

void	expand_node(t_node *node) {
	int op_kind;
	size_t i;
	size_t ret;
	t_token *head;

	head = node->word_list;
	i = 0;
	fprintf(stderr, "word_list_size : %zu i : %zu\n", node->word_list_size, i);
	while (i < node->word_list_size) {
		op_kind = node->word_list->kind;
		if (op_kind != TK_WORD_IN_SINGLE_Q && op_kind != TK_WORD_IN_DOUBLE_Q && op_kind != TK_OP_DOLLAR)
			i++;
		else if (op_kind == TK_WORD_IN_SINGLE_Q || op_kind == TK_WORD_IN_DOUBLE_Q)
		{
			handle_token_in_quotes(node->word_list);
			i++;
		}
		else if (op_kind == TK_OP_DOLLAR)
		{
			if (i == 0)
			{
				ret = expand_token(&(node->word_list), op_kind);
				i += ret;
				node->word_list_size += ret - 1;
				head = node->word_list;
			}
			else
			{
				ret = expand_token(&(node->word_list), op_kind);
				i += ret;
				node->word_list_size += ret - 1;
			}
		}
		if (node->word_list->is_join_prev == true)
		{
			join_token_and_token_prev(&(node->word_list));
			node->word_list_size -= 1;
			i--;
		}
		fprintf(stderr, "226         word_list_size : %zu i : %zu,  node->word_list->str = %s \n", node->word_list_size, i, node->word_list->str);
		node->word_list = node->word_list->next;
		}
		node->word_list = head;
	}

void	expansion(t_node *node)
{
	while (node->kind == ND_PIPE)
	{
		expand_node(node->right);
		node = node->left;
	}
	expand_node(node);
}
