#include "minishell.h"

void	export_(char **args)
{
	size_t	i;
	size_t	arg_len;
	size_t	key_len;
	size_t	val_len;
	char	*equal_at;
	char	*key;
	char	*val;

	if (args[0] == NULL)
	{
		msh_export(&(g_mshell->envlist), NULL, NULL);
		return ;
	}
	i = 0;
	while (args[i] != NULL)
	{
		if (args[0][0] == '-') // is_option
		{
			error_option("export", args[i]);
			print_command_usage("export", "export [name[=value] ...]");
			i++;
			continue ;
		}
		if (!ft_isalpha(args[i][0]))
		{
			error_ident("export", args[i]);
			i++;
			continue ;
		}
		equal_at = ft_strchr(args[i], '=');
		if (equal_at == NULL)
		{
			i++;
			continue ;
		}
		else
		{
			key_len = ft_strchr(args[i], '=') - args[i];
			key = ft_substr(args[i], 0, key_len);
			val = ft_substr(args[i], key_len + 1, ft_strlen(args[i]));
			msh_export(&(g_mshell->envlist), key, val);
			free(key);
			free(val);
			i++;
			continue ;
		}
	}
}

void	msh_export(t_envvar **envs, char *key, char *val)
{
	t_envvar	*key_at;

	if (key == NULL && val == NULL)
	{
		msh_env(*envs);
		return ;
	}
	if (*envs == NULL)
		*envs = new_envlist(key, val);
	key_at = get_envvar_with_key(*envs, key);
	if (key_at == NULL)
		add_envlist(*envs, new_envlist(key, val));
	else
		replace_val(key_at, val);
}
