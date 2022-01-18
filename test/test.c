#include "minishell.h"


//int	main(int argc, char **argv)
t_node	*main_(char *str)
{
//	if (argc == 1)
//		error("Invalid argument!\n");
	t_token	*token = tokenize(str);

	// tokenize
	if (token->kind == TK_EOF)
	{
		free(token);
		return (0);
	}
	printf("%s\n", token->prev->prev->str);
	debug_tokenize(token);
	// printf("%.*s\n", token->len, token->str);

	// parse
	t_node	*node = command_line(&token);
	printf("parse: =========================================\n");
	debug_node(node);
	 expansion(node);
	 printf("expansion: =========================================\n");
	 debug_node(node);
//	 printf("tokenize ========= token %zu\n", node->word_list_size);
//	 printf("tokenize ========= token %s\n", node->word_list->str);
	 return (node);
}

int	main(int argc, char **argv, char **envp)
{
	t_node	*node;
	char **paths;

	if (argc == 1)
	error("Invalid argument!\n");
	node = main_(argv[1]);
	paths = get_command_path(envp);
	printf("exec.c =========================================\n");
	handle_command(paths, node);
//	system("leaks minishell");
	exit (0);
}
