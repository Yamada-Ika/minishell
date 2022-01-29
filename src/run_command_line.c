#include "minishell.h"

void	run_command_line(char *cmd_line)
{
	t_token	*token;
	t_node	*node;

	token = lexer(cmd_line);
	if (token == NULL)
		return ;
	node = parser(&token);
	if (node == NULL)
		return ;
	expansion(node);
	if (node->word_list->kind != TK_EOF)
		exec_command_line(node);
	free_token_list(token->next);
	free_node_list(node);
}
