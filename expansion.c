#include "minishell.h"

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

// skip : ' '
//static size_t	join_valiable(char *p, t_token **tok)
//{
//	t_token	*cur;
//	t_token	head;
//	size_t	count;
//
//	count = 0;
//	head.next = NULL;
//	cur = &head;
//	while (*p)
//	{
//		while (*p == ' ')
//			p++;
//		if (get_word_len(p, " "))
//		{
//			count++;
//			cur->next = new_token(TK_EXP_WORD, p, get_word_len(p," "));
//			cur->next->prev = cur;
//			cur = cur->next;
//			p += cur->len;
//			continue;
//		}
//	}
//	cur->next = (*tok)->next->next;
//	cur->next->prev = cur;
//	(*tok)->prev->next = head.next;
//	head.next->prev = (*tok)->prev;
//	*tok = head.next;
//	fprintf(stderr, "count : %lld\n", count);
//	return (count);
//}

static void debug_token(t_token *token, size_t loop_cnt)
{
	const char *kind[] = {
		"TK_OP_DOUBLE_GR",
		"TK_OP_SINGLE_LS",
		"TK_OP_LS",
		"TK_OP_GR",
		"TK_OP_PIPE",
		"TK_WORD_IN_SINGLE_Q",
		"TK_WORD_IN_DOUBLE_Q",
		"TK_OP_DOLLAR",
		"TK_WORD",
		"TK_EXP_WORD",
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

//size_t	replace_token(t_token **token, char *str)
//{
//	t_token *head;
//	size_t	increase_tok_num;
//
//	head = *token;
//	if (str == NULL || *str == '\0')
//	{
//		(*token)->prev->next = (*token)->next->next;
//		(*token)->next->next->prev = head->prev;
//		*token = head->next->next;
//		free(str);
//		return (0);
//	}
//	increase_tok_num = join_valiable(str, token);
//	debug_token(head, 2);
//	free(head->next);
//	free(head);
//	return (increase_tok_num);
//}

//size_t	expand_token(t_token **token, int op_kind)
//{
//	char	*str;
//	char	*variable_name;
//
//	// fprintf(stderr,"expand_token called\n");
//	if (op_kind == TK_OP_DOLLAR)
//	{
//		variable_name = ft_substr((*token)->next->str, 0, (*token)->next->len);
//		// fprintf(stderr, "variable_name: %s\n", variable_name);
//		// str = ft_split(getenv(variable_name), ' ');
//		str = ft_strdup(getenv(variable_name));
//		if (errno)
//			error(strerror(errno));
//		if (str != NULL)
//			fprintf(stderr, "%s\n", str);
//		return (replace_token(token, str));
//	}
//	return (0);
//}

void	expand_node(t_node *node)
{
	int	op_kind;
	size_t	i;
	size_t	ret;
	t_token	*head;

	head = node->word_list;
	i = 0;
	fprintf(stderr, "word_list_size : %zu i : %zu\n", node->word_list_size, i);
	while (i < node->word_list_size)
	{
		op_kind = node->word_list->kind;
		if (op_kind != TK_WORD_IN_SINGLE_Q && op_kind != TK_WORD_IN_DOUBLE_Q && op_kind != TK_OP_DOLLAR)
			i++;
		else if (op_kind == TK_WORD_IN_SINGLE_Q || op_kind == TK_WORD_IN_DOUBLE_Q)
		{
			handle_token_in_quotes(node->word_list);
			i++;
		}
		else
		{
//			fprintf(stderr, "$$$$\n");
//			if (i == 0)
//			{
//				ret = expand_token(&(node->word_list), op_kind);
//				i += ret;
//				node->word_list_size += ret - 2;
//				fprintf(stderr, "word_list-str:  %.*s\n", node->word_list->len, node->word_list->str);
//				head = node->word_list;
//			}
//			else
//			{
//				ret = expand_token(&(node->word_list), op_kind);
//				i += ret;
//				node->word_list_size += ret - 2;
//			}
			i++;
		}
		fprintf(stderr, "word_list_size : %zu i : %zu\n", node->word_list_size, i);
		node->word_list = node->word_list->next;
	}
	node->word_list = head;
//	sum_up_token_in_quote(node);
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
