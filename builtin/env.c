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

void	msh_env(t_envvar *envs)
{
	while (envs != NULL)
	{
		printf("%s=%s\n", envs->key, envs->val);
		envs = envs->next;
	}
}
