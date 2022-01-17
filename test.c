#include "minishell.h"


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
