#include "minishell.h"

static void	_update_pwd_helper(char *path, char *key)
{
	char	*val;

	val = my_getenv(g_mshell.envlist, key);
	if (val == NULL)
		return ;
	if (path != NULL)
		msh_export(&(g_mshell.envlist), key, path);
	else
		msh_export(&(g_mshell.envlist), key, "");
}

static void	_update_pwd_in_envlist(char *path)
{
	_update_pwd_helper(path, "PWD");
}

static void	_update_oldpwd_in_envlist(char *path)
{
	_update_pwd_helper(path, "OLDPWD");
}

void	cd_(char **cmds)
{
	char	*path;
	char	*abs_path;
	char	*tmp;

	errno = ERRNO_INIT_VAL;
	path = getcwd(NULL, 0);
	if (path == NULL && errno != ERRNO_INIT_VAL)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		if (chdir(cmds[1]) == -1)
		{
			free(path);
			error_with_errno("cd", cmds[1]);
			return (add_exit_status_to_env(1));
		}
	}
	else
	{
		abs_path = ft_strjoin(path, "/");
		tmp = abs_path;
		abs_path = ft_strjoin(abs_path, cmds[1]);
		free(tmp);
		if (chdir(abs_path) == -1)
		{
			free(path);
			error_with_errno("cd", abs_path);
			return (add_exit_status_to_env(1));
		}
	}
	_update_oldpwd_in_envlist(my_getenv(g_mshell.envlist, "PWD"));
	free(path);
	add_exit_status_to_env(0);
	path = getcwd(NULL, 0);
	_update_pwd_in_envlist(path);
	free(g_mshell.pwd);
	g_mshell.pwd = path;
}
