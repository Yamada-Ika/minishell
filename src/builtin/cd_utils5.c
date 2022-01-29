#include "minishell.h"

int	chdir_for_cd(char *cano_path, char *arg_path)
{
	if (chdir(cano_path) == -1)
	{
		if (chdir(arg_path) == -1)
			return (-1);
	}
	return (0);
}
