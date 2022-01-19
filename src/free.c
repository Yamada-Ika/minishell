#include "minishell.h"

void	free_token_list(t_token *token)
{
	t_token *token_next;
	while (token->kind != TK_EOF)
	{
		free (token->str);
		token_next = token->next;
		free (token);
		token = token_next;
	}
	free (token->str);
	free(token);
}

void free_double(char **p)
{
	size_t i;
	i = 0;
	if (p == NULL)
		return;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}

void	free_t_redirect_list(t_redirect_list *redirect)
{
	while(redirect)
	{
		free(redirect->word);
		free(redirect->redirect);
		redirect = redirect->next;
	}
}

void	free_t_command(t_command cmds)
{
//	free_double(cmds.word_list);

	free(cmds.word_list);
	free_t_redirect_list(cmds.in_redir);
	free_t_redirect_list(cmds.out_redir);
}

void	free_node_element(t_node *node)
{
	free_t_command(node->command);
	free(node);
}

void	free_node_list(t_node *node)
{
	t_node	*left_node;

	while (node->left != NULL)
	{
		free_node_element(node->right);
		left_node = node->left;
		free_node_element(node);
		node = left_node;
	}
	free_node_element(node);
}
