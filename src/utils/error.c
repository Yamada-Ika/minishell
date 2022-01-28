#include "minishell.h"

t_node	*parse_error(t_node *node, t_token *token)
{
	free_token_list(token);
	if (node != NULL)
		free_node_list(node);
	return (NULL);
}

t_token	*tokenize_error(t_token *head, t_token *cur)
{
	t_token	*token_next;

	if (head == cur)
		return (NULL);
	while (head != NULL)
	{
		free (head->str);
		token_next = head->next;
		free (head);
		head = token_next;
	}
	return (NULL);
}

void	error(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	exit(1);
}

void	error_message(char *m, char *m2)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(m, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(m2, 2);
}

void	error_exit_with_message(int stats, char *m, char *m2)
{
	error_message(m, m2);
	exit(stats);
}
