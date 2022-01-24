#include "minishell.h"

void	env_(char **args)
{
	if (args[0] == NULL)
	{
		msh_env(g_mshell->envlist);
		return ;
	}
	ft_putendl_fd("env: minishell can't have arguments", STDERR_FILENO);
}

void	msh_env(t_envvar *envlist)
{
	while (envlist != NULL)
	{
		if (ft_strcmp(envlist->key, "?") != 0)
			printf("%s=%s\n", envlist->key, envlist->val);
		envlist = envlist->next;
	}
}
