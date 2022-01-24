#include "minishell.h"

void	env_(char **args)
{
	if (args[0] == NULL)
	{
		msh_env(g_mshell->envlist);
		return ;
	}
	ft_putendl_fd("env: minishell can't have arguments", STDERR_FILENO);
	add_exit_status_to_env(1);
}

void	msh_env(t_envvar *envlist)
{
	while (envlist != NULL)
	{
		if (ft_strcmp(envlist->key, "?") != 0)
			printf("%s=%s\n", envlist->key, envlist->val);
		envlist = envlist->next;
	}
	add_exit_status_to_env(0);
}
