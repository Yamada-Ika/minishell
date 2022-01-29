#include "minishell.h"

char	*gen_abs_path(char *dst)
{
	char	*cur_path;
	char	*abs_path;

	cur_path = ft_strjoin("/", dst);
	abs_path = ft_strjoin(g_mshell.pwd, cur_path);
	free(cur_path);
	return (abs_path);
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

	abs_path = gen_abs_path(rel_path);
	if (abs_path == NULL)
		error(strerror(errno));
	cano_path = get_canonical_path(abs_path);
	free(abs_path);
	return (cano_path);
}
