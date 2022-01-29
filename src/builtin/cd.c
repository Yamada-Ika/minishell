#include "minishell.h"

void	cd_(char **cmds)
{
	char	*cano_path;
	char	*arg_path;

	arg_path = NULL;
	if (cannot_get_home_path(cmds, &arg_path))
		return (add_exit_status_to_env(1));
	else if (arg_path == NULL)
		arg_path = cmds[1];
	if (is_abs_path(arg_path))
		cano_path = gen_abs_to_cano_path(arg_path);
	else if (is_arg_path_start_from_current_dir(arg_path))
		cano_path = gen_rel_to_cano_path(arg_path);
	else
	{
		if (can_chdir_with_cdpath(arg_path, &cano_path))
			return (cd_do_cdpath_routine(cano_path));
		cano_path = gen_rel_to_cano_path(arg_path);
	}
	if (cano_path == NULL)
		return (add_exit_status_to_env(1));
	if (chdir_for_cd(cano_path, arg_path) == -1)
		return (cd_do_error_routine(cano_path, arg_path));
	cd_do_success_routine(cano_path);
}
