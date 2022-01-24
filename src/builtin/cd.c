#include "minishell.h"

static void	_update_pwd_helper(char *key)
{
	char	*path;
	char	*val;

	val = my_getenv(g_mshell->envlist, key);
	if (val == NULL)
		return ;
	path = getcwd(NULL, 0);
	if (path != NULL)
		msh_export(&(g_mshell->envlist), key, path);
	free(path);
}

static void	_update_pwd_in_envlist(void)
{
	_update_pwd_helper("PWD");
}

static void	_update_oldpwd_in_envlist(void)
{
	_update_pwd_helper("OLDPWD");
}

void	cd_(char **cmds)
{
	int	exit_status;

	_update_oldpwd_in_envlist();
	exit_status = 0;
	if (chdir(cmds[1]) == -1)
		exit_status = 1;
	add_exit_status_to_env(exit_status);
	_update_pwd_in_envlist();
}
