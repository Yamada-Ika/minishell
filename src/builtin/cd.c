#include "minishell.h"

static void	_update_pwd(char *key, char *path)
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

static char	*_get_abs_path(char *dst)
{
	char	*cur_path;
	char	*abs_path;
	char	*home_path;

	if (dst == NULL)
	{
		home_path = my_getenv(g_mshell.envlist, "HOME");
		if (home_path == NULL)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
			return (NULL);
		}
		abs_path = ft_strdup(home_path);
	}
	else
	{
		cur_path = ft_strjoin("/", dst);
		abs_path = ft_strjoin(g_mshell.pwd, cur_path);
		free(cur_path);
	}
	return (abs_path);
}

void	cd_(char **cmds)
{
	char	*abs_path;
	char	*cano_path;

	abs_path = _get_abs_path(cmds[1]);
	if (abs_path == NULL)
		return (add_exit_status_to_env(1));
	cano_path = get_canonical_path(abs_path);
	free(abs_path);
	if (chdir(cano_path) == -1)
	{
		error_with_errno("cd", cano_path);
		if (chdir(cmds[1]) == -1)
		{
			error_with_errno("cd", cmds[1]);
			return (add_exit_status_to_env(1));
		}
	}
	_update_pwd("OLDPWD", my_getenv(g_mshell.envlist, "PWD"));
	_update_pwd("PWD", cano_path);
	free(g_mshell.pwd);
	g_mshell.pwd = cano_path;
	add_exit_status_to_env(0);
}
