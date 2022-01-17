#include "minishell.h"

void	run_command_line(char *str, char **paths)
{
	t_token	*token;

	printf("run_command_line 7:  str = %s\n", str);
	token = tokenize(str);
//	debug_tokenize(token);
	// parse
	t_node	*node = command_line(&token);
//	printf("parse: =========================================\n");
//	debug_node(node);
	expansion(node);
	handle_command(paths, node);
//	printf("expansion: =========================================\n");
//	debug_node(node);
}
