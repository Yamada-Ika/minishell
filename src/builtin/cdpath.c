#include "minishell.h"

static char	*_strjoin1(char *s1, char *s2)
{
	char	*tmp_for_free;
	char	*joined_s;

	tmp_for_free = s1;
	joined_s = ft_strjoin(s1, s2);
	free(tmp_for_free);
	return (joined_s);
}

static char	*_gen_abs_cdpath(char *cano_cdpath, char *arg_path)
{
	char	*abs_cdpath;
	char	*abs_arg_path;
	char	*tmp_for_free;

	abs_cdpath = gen_abs_path(cano_cdpath);
	abs_arg_path = ft_strjoin("/", arg_path);
	tmp_for_free = abs_cdpath;
	abs_cdpath = ft_strjoin(abs_cdpath, abs_arg_path);
	free(tmp_for_free);
	free(abs_arg_path);
	return (abs_cdpath);
}

static char	*_gen_cano_path_from_cdpath_helper(char **cdpaths, char *arg_path)
{
	char	*abs_cdpath;
	char	*cano_cdpath;
	size_t	i;

	i = 0;
	while (cdpaths[i] != NULL)
	{
		if (is_abs_path(cdpaths[i]))
			cano_cdpath = gen_abs_to_cano_path(cdpaths[i]);
		else
			cano_cdpath = cdpaths[i];
		if (is_abs_path(cano_cdpath))
			abs_cdpath = _strjoin1(cano_cdpath, arg_path);
		else
			abs_cdpath = _gen_abs_cdpath(cano_cdpath, arg_path);
		if (chdir(abs_cdpath) != -1)
		{
			free_strs(cdpaths);
			return (abs_cdpath);
		}
		free(abs_cdpath);
		i++;
	}
	free_strs(cdpaths);
	return (NULL);
}

static char	**_get_cdpaths(void)
{
	char	*cdpath;
	char	**cdpaths;

	cdpath = my_getenv(g_mshell.envlist, "CDPATH");
	if (cdpath == NULL)
		return (NULL);
	cdpaths = ft_split(cdpath, ':');
	if (cdpaths == NULL)
		error(strerror(errno));
	return (cdpaths);
}

char	*gen_cano_path_from_cdpath(char *arg_path)
{
	char	*abs_path;
	char	*cano_path;
	char	**cdpaths;

	cdpaths = _get_cdpaths();
	if (cdpaths == NULL)
		return (NULL);
	abs_path = _gen_cano_path_from_cdpath_helper(cdpaths, arg_path);
	cano_path = get_canonical_path(abs_path);
	free(abs_path);
	return (cano_path);
}
