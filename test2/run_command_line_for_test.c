#include "minishell.h"

void	run_command_line(char *cmd_line)
{
	t_token	*token;
	t_node	*node;

	// fprintf(stderr, "run_command_line 7: cmd_line = %s\n", cmd_line);
	token = tokenize(cmd_line);
	if (token == NULL)
		return ;
//	 fprintf(stderr, "DEBUG TOKENIZE START : =========================================\n");
//	 debug_tokenize(token);
//	 fprintf(stderr, "DEBUG TOKENIZE END   : =========================================\n");
	node = command_line(&token);
	if (node == NULL)
		return ;
//	 fprintf(stderr, "DEBUG PARSE START    : =========================================\n");
//	 debug_node(node);
//	 fprintf(stderr, "DEBUG PARSE END      : =========================================\n");
	expansion(node);
//	 fprintf(stderr, "DEBUG EXPAND START   : =========================================\n");
//	 debug_node(node);
//	 fprintf(stderr, "DEBUG EXPAND END     : =========================================\n");
	if (node->word_list->kind != TK_EOF)
		handle_command(node);
	free_token_list(token->next);
	free_node_list(node);
}
