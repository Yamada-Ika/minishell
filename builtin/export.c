#include "minishell.h"

void	msh_export_wrapper(char *key, char *val)
{
	msh_export(&(g_mshell->envlist), key, val);
}

void	msh_export(t_envvar **envs, char *key, char *val)
{
	if (key == NULL && val == NULL)
		msh_env(*envs);
	else if (*envs == NULL)
		*envs = new_envlist(key, val);
	else
		add_envlist(*envs, new_envlist(key, val));
}
