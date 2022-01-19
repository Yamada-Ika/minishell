#include "envvar.h"

void	env(t_envvar *envs)
{
	while (envs != NULL)
	{
		printf("%s=%s\n", envs->key, envs->val);
		envs = envs->next;
	}
}
