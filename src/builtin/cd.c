#include "minishell.h"

void	cd_(char **cmds)
{
	int	exit_status;

	exit_status = 0;
	if (chdir(cmds[1]) == -1)
		exit_status = 1;
	add_exit_status_to_env(exit_status);
}
