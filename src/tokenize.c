#include "minishell.h"

t_token	*tokenize_error(t_token *token)
{
	t_token *token_next;
	while (token != NULL)
	{
		free (token->str);
		token_next = token->next;
		free (token);
		token = token_next;
	}
	return (NULL);
}

t_token	*new_token(t_token *cur, t_token_kind kind, char **p, size_t len)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		error("malloc error\n");
	new->kind = kind;
	new->is_join_prev = false;
	new->str = ft_substr(*p, 0, len);
	new->len = len;
	if (cur->kind != -1  && *(*p - 1) != ' ' && !is_redirect_kind(cur->kind) &&
		cur->kind != TK_OP_PIPE && !is_redirect_kind(kind) && kind != TK_OP_PIPE)
		new->is_join_prev = true;
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
	while (kw[i] != NULL)
	{
		if (!ft_strncmp(kw[i], p, ft_strlen(kw[i])))
			return (ft_strlen(kw[i]));
		i++;
	}
	return (0);
}

static	t_token_kind	_get_word_kind(char *p)
{
	t_token_kind	kind;

	kind = TK_WORD;
	while (*p)
	{
		if (*p == '\'' && kind != TK_WORD_IN_DOUBLE_Q)
		{
			if (kind == TK_WORD_IN_SINGLE_Q)
				return (TK_WORD_IN_SINGLE_Q);
			kind = TK_WORD_IN_SINGLE_Q;
		}
		if (*p =='"' && kind != TK_WORD_IN_SINGLE_Q)
		{
			if (kind == TK_WORD_IN_DOUBLE_Q)
				return (TK_WORD_IN_DOUBLE_Q);
			kind = TK_WORD_IN_DOUBLE_Q;
		}
		if (kind == TK_WORD && ft_strchr(" ><|", *p))
			return (TK_WORD);
		if (kind == TK_WORD && *p == '$' && ft_isalnum(*(p + 1)))
			return (TK_OP_DOLLAR);
		p++;
	}
	if (kind != TK_WORD)
	{
		ft_putstr_fd("quote error\n", 2);
		kind = -1;
	}
	return (kind);
}

static void	_skip_space(char **s)
{
	while (**s == ' ')
		(*s)++;
}

t_token	*tokenize(char *p)
{
	t_token			*cur;
	t_token			head;
	t_token_kind	word_kind;
	size_t			op_len;

	head.kind = -1;
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
			if (word_kind == -1)
			{
				cur->next = NULL;
				return (tokenize_error(head.next));
			}
			cur = new_token(cur, word_kind, &p, get_word_len(p, word_kind, " ><|'\"" ));
		}
	}
	cur = new_token(cur, TK_EOF, &p, 0);
	cur->next = head.next;
	head.next->prev = cur;
	return (head.next);
}
