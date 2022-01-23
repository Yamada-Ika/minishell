#include "minishell.h"

t_node	*parse_error(t_node *node, t_token *token)
{
	free_token_list(token);
	if (node != NULL)
		free_node_list(node);
	return (NULL);
}

void	error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}
