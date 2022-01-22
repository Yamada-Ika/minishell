#include "minishell.h"

void	env_(char **args)
{
	size_t	i;
//	char	*equal_at;

	if (args[0] == NULL)
	{
		msh_env(g_mshell->envlist);
		return ;
	}
	i = 0;
	while (args[i] != NULL)
	{
		if (args[0][0] == '-' && ft_strlen(args[0]) >= 2)
		{
			error_option2("env", args[i][1]);
			print_command_usage2("env", "env [name=value ...]");
			return ;
		}
		i++;
	}
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
