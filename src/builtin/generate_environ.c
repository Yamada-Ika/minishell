#include "minishell.h"

static char	*_multi_strdup(char *top, char *mid, char *end)
{
	char	*s;
	char	*tmp_for_free;

	s = ft_strjoin(top, mid);
	tmp_for_free = s;
	s = ft_strjoin(s, end);
	free(tmp_for_free);
	return (s);
}

static size_t	_get_envlist_size(t_envvar *envlist)
{
	size_t		size;

	size = 0;
	while (envlist != NULL)
	{
		if (ft_strcmp(envlist->key, "?") != 0)
			size++;
		envlist = envlist->next;
	}
	return (size);
}

static void	_set_environ_from_envlist(char **envs, t_envvar *envlist)
{
	size_t	i;

	i = 0;
	while (envlist != NULL)
	{
		if (ft_strcmp(envlist->key, "?") != 0)
		{
			envs[i] = _multi_strdup(envlist->key, "=", envlist->val);
			i++;
		}
		envlist = envlist->next;
	}
}

char	**generate_environ(void)
{
	char	**envs;
	size_t	size;

	size = _get_envlist_size(g_mshell.envlist);
	envs = (char **)ft_calloc(size + 1, sizeof(char *));
	if (envs == NULL)
		error(strerror(errno));
	_set_environ_from_envlist(envs, g_mshell.envlist);
	return (envs);
}
