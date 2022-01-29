#include "minishell.h"

t_token	*new_token(t_token *cur, t_token_kind kind, char **p, size_t len)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		error(strerror(errno));
	new->kind = kind;
	new->is_join_prev = false;
	new->str = ft_substr(*p, 0, len);
	new->len = len;
	if (cur->kind != EMPTY && *(*p - 1) != ' ' && !is_redirect_kind(cur->kind)
		&&cur->kind != TK_OP_PIPE && !is_redirect_kind(kind)
		&& kind != TK_OP_PIPE && kind != TK_EOF)
		new->is_join_prev = true;
	cur->next = new;
	new->prev = cur;
	*p += len;
	return (new);
}

static size_t	_get_operator_len(char *p)
{
	const char	*kw[] = {"<<", ">>", "<", ">", "|", NULL};
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
		if ((*p == '\'' || *p == '"') && is_quote_closed(*p, kind))
			return (kind);
		if (*p == '\'' && kind != TK_WORD_IN_DOUBLE_Q)
			kind = TK_WORD_IN_SINGLE_Q;
		if (*p == '"' && kind != TK_WORD_IN_SINGLE_Q)
			kind = TK_WORD_IN_DOUBLE_Q;
		if (kind == TK_WORD && ft_strchr(" ><|", *p))
			return (TK_WORD);
		if (kind == TK_WORD && is_env_name(p))
			return (TK_OP_DOLLAR);
		p++;
	}
	if (kind != TK_WORD)
	{
		ft_putstr_fd("quote error\n", 2);
		kind = EMPTY;
	}
	return (kind);
}

t_token	*lexer(char *p)
{
	t_token			*cur;
	t_token			head;
	t_token_kind	kind;
	size_t			op_len;

	head.kind = EMPTY;
	cur = &head;
	while (*p)
	{
		skip_space(&p);
		op_len = _get_operator_len(p);
		if (op_len != 0)
			cur = new_token(cur, check_op(p), &p, op_len);
		else if (*p)
		{
			kind = _get_word_kind(p);
			if (kind == EMPTY)
				return (tokenize_error(head.next, cur->next));
			cur = new_token(cur, kind, &p, get_word_len(p, kind, " ><|'\"" ));
		}
	}
	cur = new_token(cur, TK_EOF, &p, 0);
	cur->next = head.next;
	head.next->prev = cur;
	return (head.next);
}
