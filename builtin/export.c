#include "envvar.h"

void	msh_export(t_envvar **envs, char *key, char *val)
{
	if (key == NULL && val == NULL)
		msh_env(*envs);
	else if (*envs == NULL)
		*envs = new_envlist(key, val);
	else
		add_envlist(*envs, new_envlist(key, val));
}
