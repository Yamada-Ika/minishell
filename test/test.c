#include "minishell.h"

#ifdef ALL
#define TOKEN 1
#define PARSE 1
#define EXPAND 1
#endif

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_token	*token;
	t_node	*node;
	char	**paths;

	if (argc == 1)
		error("Invalid argument!\n");
	str = argv[1];

	// tokenize
	token = tokenize(str);

	#ifdef TOKEN
	printf("tokenize =========================================\n");
	debug_tokenize(token);
	#endif

	// parse
	node = command_line(&token);
	#ifdef PARSE
	printf("parse =========================================\n");
	debug_node(node);
	#endif

	// expansion
	expansion(node);
	#ifdef EXPAND
	printf("expand =========================================\n");
	debug_node(node);
	#endif

	// handle_command
	// printf("exec =========================================\n");
	// paths = get_command_path(envp);
	// handle_command(paths, node);
//	system("leaks minishell");
	exit (0);
}
