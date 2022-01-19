#include "minishell.h"

#ifdef ALL
#define TOKEN 1
#define PARSE 1
#define EXPAND 1
#endif

__attribute__((destructor))
void	destructor(void)
{
	int	status;

	system("leaks debug");
//	status = system("leaks debug &> leaksout");
//	if (status)
//	{
//		write(2, "leak!!!\n", 8);
//		system("cat leaksout >/dev/stderr");
//		exit(1);
//	}
}

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
	free_token_list(token);
	free_node_list(node);

	// handle_command
	// printf("exec =========================================\n");
	// paths = get_command_path(envp);
	// handle_command(paths, node);
	return (0);
//	exit (0);
}
