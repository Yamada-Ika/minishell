#include "minishell.h"

static bool	_is_invalid_redirect(t_token *tok)
{
	if (is_redirect_kind(tok->kind) && (is_redirect_kind(tok->next->kind)
			|| tok->next->kind == TK_OP_PIPE || tok->next->kind == TK_EOF))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(tok->next->str, 2);
		ft_putstr_fd("'\n", 2);
		add_exit_status_to_env(258);
		return (true);
	}
	return (false);
}

size_t	count_command_size(t_token **tok)
{
	size_t	cnt;

	cnt = 0;
	while ((*tok)->kind != TK_EOF && (*tok)->kind != TK_OP_PIPE)
	{
		if (_is_invalid_redirect(*tok))
			return (0);
		cnt++;
		(*tok) = (*tok)->next;
	}
	return (cnt);
}

t_node	*new_node_command(t_token **tok)
{
	t_node	*node;

	if ((*tok)->kind == TK_EOF || (*tok)->kind == TK_OP_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		add_exit_status_to_env(258);
		return (NULL);
	}
	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (node == NULL)
		error(strerror(errno));
	node->word_list = *tok;
	node->word_list_size = count_command_size(tok);
	if (node->word_list_size == 0)
	{
		free(node);
		return (NULL);
	}
	node->kind = ND_CMD;
	return (node);
}

t_node	*new_node_pipe(t_token *token, t_node *left, t_node *right)
{
	t_node	*node;

	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (node == NULL)
		error(strerror(errno));
	node->left = left;
	node->right = right;
	node->kind = ND_PIPE;
	node->word_list = token;
	node->word_list_size = 1;
	return (node);
}

t_node	*parser(t_token **tok)
{
	t_token	*tmp_tk;
	t_token	*tk_eof;
	t_node	*node;
	t_node	*tmp_nd;

	tk_eof = (*tok)->prev;
	node = new_node_command(tok);
	if (node == NULL)
		return (parse_error(node, tk_eof->next));
	while ((*tok)->kind == TK_OP_PIPE)
	{
		tmp_tk = *tok;
		*tok = (*tok)->next;
		tmp_nd = new_node_command(tok);
		if (tmp_nd == NULL)
			return (parse_error(node, tk_eof->next));
		node = new_node_pipe(tmp_tk, node, tmp_nd);
	}
	*tok = tk_eof;
	return (node);
}
