#include "minishell.h"


int	main(int argc, char **argv)
{
	if (argc == 1)
	error("Invalid argument!\n");
	main_(argv[1]);
//	system("leaks minishell");
	exit (0);
}
