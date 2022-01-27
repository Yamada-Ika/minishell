#include "minishell.h"

static void	_update_pwd(char *key, char *path)
{
	if (!is_exist_key(g_mshell.envlist, key))
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

	cur_path = ft_strjoin("/", dst);
	abs_path = ft_strjoin(g_mshell.pwd, cur_path);
	free(cur_path);
	return (abs_path);
}

bool	is_non_arguments(char **args)
{
	return (args[1] == NULL);
}

bool	is_abs_path(char *path)
{
	return (path[0] == '/');
}

char	*get_home_path(void)
{
	char	*home_path;

	home_path = my_getenv(g_mshell.envlist, "HOME");
	if (home_path == NULL)
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (NULL);
	}
	if (home_path[0] == '\0')
	{
		return (g_mshell.pwd);
	}
	return (home_path);
}

char	*gen_abs_to_cano_path(char *abs_path)
{
	char	*cano_path;
	char	*tmp_for_free;

	cano_path = get_canonical_path(abs_path);
	if (cano_path == NULL)
		error(strerror(errno));
	if (cano_path[0] != '\0')
		return (cano_path);
	tmp_for_free = cano_path;
	cano_path = ft_strjoin("/", cano_path);
	if (cano_path == NULL)
		error(strerror(errno));
	free(tmp_for_free);
	return (cano_path);
}

char	*gen_rel_to_cano_path(char *rel_path)
{
	char	*abs_path;
	char	*cano_path;

	abs_path = _get_abs_path(rel_path);
	if (abs_path == NULL)
		error(strerror(errno));
	cano_path = get_canonical_path(abs_path);
	free(abs_path);
	return (cano_path);
}

int	chdir_for_cd(char *cano_path, char *arg_path)
{
	if (chdir(cano_path) == -1)
	{
		if (chdir(arg_path) == -1)
			return (-1);
	}
	return (0);
}

char	*gen_cano_path_from_cdpath(char *arg_path)
{
	char	*cdpath;
	char	**cdpaths;
	char	*abs_cdpath;
	char	*abs_arg_path;
	char	*tmp_for_free;
	size_t	i;

	cdpath = my_getenv(g_mshell.envlist, "CDPATH");
	if (cdpath == NULL)
		return (NULL);
	cdpaths = ft_split(cdpath, ':');
	if (cdpaths == NULL)
		error(strerror(errno));
	i = 0;
	while (cdpaths[i] != NULL)
	{
		if (is_abs_path(cdpaths[i]))
			abs_cdpath = ft_strjoin(cdpaths[i], arg_path);
		else
		{
			abs_cdpath = _get_abs_path(cdpaths[i]);
			abs_arg_path = ft_strjoin("/", arg_path);
			tmp_for_free = abs_cdpath;
			abs_cdpath = ft_strjoin(abs_cdpath, abs_arg_path);
			free(tmp_for_free);
			free(abs_arg_path);
		}
		if (chdir(abs_cdpath) != -1)
			return (abs_cdpath);
		i++;
	}
	free_strs(cdpaths);
	return (NULL);
}

void	update_pwd(char *cur_dir_path)
{
	_update_pwd("OLDPWD", my_getenv(g_mshell.envlist, "PWD"));
	_update_pwd("PWD", cur_dir_path);
	free(g_mshell.pwd);
	g_mshell.pwd = cur_dir_path;
}

void	cd_(char **cmds)
{
	char	*cano_path;
	char	*abs_path;
	char	*arg_path;

	if (is_non_arguments(cmds))
		arg_path = get_home_path();
	else
		arg_path = cmds[1];
	if (is_abs_path(arg_path))
		cano_path = gen_abs_to_cano_path(arg_path);
	else
	{
		abs_path = gen_cano_path_from_cdpath(arg_path);
		cano_path = get_canonical_path(abs_path);
		free(abs_path);
		if (cano_path != NULL)
		{
			printf("%s\n", cano_path);
			update_pwd(cano_path);
			return (add_exit_status_to_env(0));
		}
		cano_path = gen_rel_to_cano_path(arg_path);
	}
	if (cano_path == NULL)
		return (add_exit_status_to_env(1));
	if (chdir_for_cd(cano_path, cmds[1]) == -1)
	{
		error_with_errno("cd", cmds[1]);
		return (add_exit_status_to_env(1));
	}
	add_exit_status_to_env(0);
	update_pwd(cano_path);
}
