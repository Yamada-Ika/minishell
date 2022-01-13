#include "minishell.h"

size_t	replace_token(t_token *token, char **str)
{
	t_token *head;

	*head = *token;
	if (str == NULL)
	{
		token->next = token->next->next->next;
		token->next->prev = head->prev;
		return (2);
	}
	return (0);
}

size_t	expand_token(t_token *token, int op_kind)
{
	char	**str;

	if (op_kind == OP_Dollar)
	{
		str = ft_split(getenv(token->next->str), ' ');
		if (errno)
			error(strerror(errno));
		return (replace_token(token, str));
	}
}

void	expand_node(t_node *node)
{
	int	op_kind;
	size_t	i;

	i = 0;
	while (i < node->word_list_size)
	{
		op_kind = check_op(node->word_list);
		if (op_kind != OP_SINGLE_Q || op_kind != OP_DOUBLE_Q || op_kind != OP_Dollar)
			i++;
		else
			i += expand_token(node->word_list, op_kind);
		node->word_list = node->word_list->next;
	}
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