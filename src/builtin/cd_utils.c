#include "minishell.h"

bool	is_non_arguments(char **args)
{
	return (args[1] == NULL);
}

bool	is_abs_path(char *path)
{
	if (path == NULL)
		return (false);
	return (path[0] == '/');
}

bool	is_arg_path_start_from_current_dir(char *path)
{
	return (path[0] == '.');
}

bool	cannot_get_home_path(char **cmds, char **arg_path)
{
	if (is_non_arguments(cmds))
	{
		*arg_path = get_home_path();
		if (*arg_path == NULL)
			return (true);
	}
	return (false);
}

bool	can_chdir_with_cdpath(char *arg_path, char **cano_path)
{
	*cano_path = gen_cano_path_from_cdpath(arg_path);
	return (*cano_path != NULL);
}
