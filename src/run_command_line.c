#include "minishell.h"

void	run_command_line(char *cmd_line)
{
	t_token	*token;
	t_node	*node;

	fprintf(stderr, "run_command_line 7: cmd_line = %s\n", cmd_line);
	token = tokenize(cmd_line);
	if (token == NULL)
		return;
	debug_tokenize(token);
	node = command_line(&token);
	if (node == NULL)
		return;
	printf("parse    : =========================================\n");
	debug_node(node);
	expansion(node);
	printf("expansion: =========================================\n");
	debug_node(node);
	printf("run_command_line 21:  node-word_list-str = %s, kind = %d\n", node->word_list->str, node->word_list->kind);
	if (node->word_list->kind != TK_EOF)
		handle_command(node);
	free_token_list(token->next);
	free_node_list(node);
}
