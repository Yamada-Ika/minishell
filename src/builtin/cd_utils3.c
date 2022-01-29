#include "minishell.h"

void	cd_do_success_routine(char *cano_path)
{
	add_exit_status_to_env(0);
	update_pwd(cano_path);
}

void	cd_do_cdpath_routine(char *cano_path)
{
	ft_putendl_fd(cano_path, STDOUT_FILENO);
	cd_do_success_routine(cano_path);
}

void	cd_do_error_routine(char *cano_path, char *arg_path)
{
	free(cano_path);
	error_with_errno("cd", arg_path);
	add_exit_status_to_env(1);
}
