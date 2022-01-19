#include "minishell.h"

void	inherite_env_val_wrapper(char **envp)
{
	inherite_env_val(&(g_mshell->envlist), envp);
}

void	inherite_env_val(t_envvar **env_list, char **envp)
{
	size_t	i;
	size_t	key_len;
	char	*key;
	char	*val;

	if (env_list == NULL)
		exit(1);
	i = 0;
	while (envp[i] != NULL)
	{
		key_len = ft_strchr(envp[i], '=') - envp[i];
		key = ft_substr(envp[i], 0, key_len);
		val = ft_substr(envp[i], key_len + 1, ft_strlen(envp[i]));
		msh_export(env_list, key, val);
		i++;
	}
}
