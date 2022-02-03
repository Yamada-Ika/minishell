#include "minishell.h"

static void	_set_pwd(void)
{
	char	*pwd_path;

	pwd_path = getcwd(NULL, 0);
	if (pwd_path == NULL)
	{
		ft_putstr_fd("shell-init: error retrieving current directory: \
getcwd: cannot access parent directories: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(0);
	}
	g_mshell.pwd = pwd_path;
}

void	init_global_var(void)
{
	extern char	**environ;

	inherite_env_val(&(g_mshell.envlist), environ);
	msh_unset(&(g_mshell.envlist), "OLDPWD");
	msh_export(&(g_mshell.envlist), "OLDPWD", NULL);
	increment_shlvl();
	set_exit_status(0);
	g_mshell.interrupt = false;
	_set_pwd();
}
