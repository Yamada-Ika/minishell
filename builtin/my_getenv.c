#include "minishell.h"

char	*my_getenv(t_envvar *envs, char *key)
{
//	char	*val;

	if (envs == NULL)
		return (NULL);
	while (envs != NULL)
	{
		if (ft_strcmp(key, envs->key) == 0)
			return (envs->val);
		envs = envs->next;
	}
	return (NULL);
}
