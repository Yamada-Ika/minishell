#include "minishell.h"

void	run_command_line(char *cmd_line)
{
	t_token	*token;
	t_node	*node;

	// fprintf(stderr, "run_command_line 7: cmd_line = %s\n", cmd_line);
	token = lexer(cmd_line);
	if (token == NULL)
		return ;
//	 fprintf(stderr, "DEBUG lexer START : =========================================\n");
//	 debug_tokenize(token);
//	 fprintf(stderr, "DEBUG lexer END   : =========================================\n");
	node = parser(&token);
	if (node == NULL)
		return ;
//	 fprintf(stderr, "DEBUG PARSE START    : =========================================\n");
//	 debug_node(node);
//	 fprintf(stderr, "DEBUG PARSE END      : =========================================\n");
	expander(node);
//	 fprintf(stderr, "DEBUG EXPAND START   : =========================================\n");
//	 debug_node(node);
//	 fprintf(stderr, "DEBUG EXPAND END     : =========================================\n");
	if (node->word_list->kind != TK_EOF)
		exec_command_line(node);
	free_token_list(token->next);
	free_node_list(node);
}
