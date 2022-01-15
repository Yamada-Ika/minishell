#include "minishell.h"

t_token	*new_token(t_token *cur, t_token_kind kind, char **p, size_t len)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		error("malloc error\n");
	new->kind = kind;
	new->str = *p;
	new->len = len;
	cur->next = new;
	new->prev = cur;
	*p += len;
	return (new);
}

static size_t _get_operator_len(char *p)
{
	const char *kw[] = {"<<", ">>", "<", ">", "|", NULL};
	size_t		i;

	i = 0;
	// if (*p == '$' && *(p + 1) != ' ')
	// 	return (1);
	while (kw[i] != NULL)
	{
		if (!ft_strncmp(kw[i], p, ft_strlen(kw[i])))
			return (ft_strlen(kw[i]));
		i++;
	}
	return (0);
}

static t_token_kind	_get_word_kind(char *p)
{
	t_token_kind	kind;

	kind = TK_WORD;
	while (*p)
	{
		if (*p == '\'' && kind != TK_WORD_IN_DOUBLE_Q)
		{
			if (kind == TK_WORD_IN_SINGLE_Q)
				return (kind);
			kind = TK_WORD_IN_SINGLE_Q;
		}
		if (*p =='"' && kind != TK_WORD_IN_SINGLE_Q)
		{
			if (kind == TK_WORD_IN_DOUBLE_Q)
				return (kind);
			kind = TK_WORD_IN_DOUBLE_Q;
		}
		// fprintf(stderr, "56 : kind %d\n", kind);
		if (kind == TK_WORD && ft_strchr(" ><|", *p))
			return (kind);
		if (kind == TK_WORD && *p == '$' && !ft_strchr(" $", *(p + 1)))
			return (TK_OP_DOLLAR);
		p++;
	}
	if (kind != TK_WORD)
		error("quote error\n");
	return (kind);
}

static void	_skip_space(char **s)
{
	while (**s == ' ')
		(*s)++;
}

t_token *tokenize(char *p)
{
	t_token			*cur;
	t_token			head;
	t_token_kind	word_kind;
	size_t			op_len;

	head.next = NULL;
	cur = &head;
	while (*p)
	{
		_skip_space(&p);
		if (*p == '\0')
			break ;
		op_len = _get_operator_len(p);
		if (op_len != 0)
			cur = new_token(cur, check_op(p), &p, op_len);
		else
		{
			word_kind = _get_word_kind(p);
			cur = new_token(cur, word_kind, &p, get_word_len(p, word_kind, " ><|'\"" ));
		}
	}
	cur = new_token(cur, TK_EOF, &p, 0);
	cur->next = head.next;
	head.next->prev = cur;
	return (head.next);
}

void debug_tokenize(t_token *token)
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
		"TK_EXP_WORD",
		"TK_EOF",
	};
	while (token->kind != TK_EOF)
	{
		if (token == NULL)
			continue ;
		printf("{kind:%20s, str:%.*s, prev->kind:%20s, prev->str:%.*s}\n", 
			kind[token->kind],
			token->len,
			token->str,
			kind[token->prev->kind],
			token->prev->len,
			token->prev->str
			);
		token = token->next;
	}
}

void	debug_node(t_node *node)
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
		"TK_EXP_WORD",
		"TK_EOF",
	};

	while (node != NULL)
	{
		t_token	*head_left;
		size_t i_left = 0;
		head_left = node->word_list;
		while (i_left < node->word_list_size)
		{
			printf("left:::::: word_list_size %zu word_list->str %.*s word_list->kind %s\n",
				node->word_list_size,
				node->word_list->len,
				node->word_list->str,
				kind[node->word_list->kind]
			);
			i_left++;
			node->word_list = node->word_list->next;
		}
		node->word_list = head_left;
		if (node->right != NULL)
		{
			t_token	*head_right;
			size_t i_right = 0;
			head_right = node->right->word_list;
			while (i_right < node->right->word_list_size)
			{
				printf("right:::::: word_list_size %zu word_list->str %.*s word_list->kind %s\n",
					node->right->word_list_size,
					node->right->word_list->len,
					node->right->word_list->str,
					kind[node->right->word_list->kind]
				);
				i_right++;
				node->right->word_list = node->right->word_list->next;
			}
			node->right->word_list = head_right;
		}
		node = node->left;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		error("Invalid argument!\n");
	t_token	*token = tokenize(argv[1]);

	// tokenize
	if (token->kind == TK_EOF)
	{
		free(token);
		return (0);
	}
	printf("%s\n", token->prev->prev);
	debug_tokenize(token);
	// printf("%.*s\n", token->len, token->str);

	// parse
	t_node	*node = command_line(&token);
	printf("parse: =========================================\n");
	debug_node(node);
	 expansion(node);
	 printf("expansion: =========================================\n");
	 debug_node(node);
}
