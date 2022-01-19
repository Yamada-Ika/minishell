#include "minishell.h"

void	run_command_line(char *str, char **paths)
{
	t_token	*token;

	printf("run_command_line 7:  str = %s\n", str);
	token = tokenize(str);
	if (token == NULL)
		return;
	debug_tokenize(token);
	// parse
	t_node	*node = command_line(&token);
	printf("parse: =========================================\n");
	debug_node(node);
	printf("expansion: =========================================\n");
	expansion(node);
	debug_node(node);
	handle_command(paths, node);
	free_token_list(token->next);
	free_node_list(node);
}
