#include "minishell.h"

char	*my_getenv_wrapper(char *key)
{
	return (my_getenv(g_mshell->envlist, key));
}

// keyが見つかったらstrdupしてvalを返す
// そうしたら、double freeを防げる気がする
// いやどうだろ、あえてしない方が関数外でfreeする必要ないし良いかも
char	*my_getenv(t_envvar *envs, char *key)
{
	char	*val;

	if (envs == NULL)
		return (NULL);
	while (envs != NULL)
	{
		if (ft_strcmp(key, envs->key) == 0)
		{
			val = ft_strdup(envs->val);
			if (val == NULL)
				exit(1);
			return (val);
		}
		envs = envs->next;
	}
	return (NULL);
}
