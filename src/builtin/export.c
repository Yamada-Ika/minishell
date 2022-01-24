#include "minishell.h"

static void	get_key_and_val(char **key, char **val, char *equal_at, char *str)
{
	size_t		key_len;
	t_envvar	*key_at;

	if (*(equal_at - 1) != '+')
	{
		key_len = equal_at - str;
		*key = ft_substr(str, 0, key_len);
		*val = ft_substr(str, key_len + 1, ft_strlen(str));
		return ;
	}
	key_len = equal_at - 1 - str;
	*key = ft_substr(str, 0, key_len);
	*val = ft_substr(str, key_len + 2, ft_strlen(str));
	key_at = get_envvar_with_key(g_mshell->envlist, *key);
	if (key_at != NULL)
		*val = strjoin_and_free(ft_strdup(key_at->val), *val);
}

void	export_(char **args)
{
	size_t		i;
	char		*equal_at;
	char		*key;
	char		*val;

	if (args[0] == NULL)
	{
		msh_export(&(g_mshell->envlist), NULL, NULL);
		return (add_exit_status_to_env(0));
	}
	i = 0;
	while (args[i] != NULL)
	{
		if (!ft_isalpha(args[i][0]))
		{
			error_ident("export", args[i]);
			add_exit_status_to_env(1);
		}
		else
		{
			equal_at = ft_strchr(args[i], '=');
			if (equal_at != NULL)
			{
				get_key_and_val(&key, &val, equal_at, args[i]);
				msh_export(&(g_mshell->envlist), key, val);
				add_exit_status_to_env(0);
				free(key);
				free(val);
			}
		}
		i++;
	}
}

static void	_display_env(t_envvar *envlist)
{
	while (envlist != NULL)
	{
		if (ft_strcmp(envlist->key, "?") != 0)
			printf("declare -x %s=\"%s\"\n", envlist->key, envlist->val);
		envlist = envlist->next;
	}
}

void	msh_export(t_envvar **envs, char *key, char *val)
{
	t_envvar	*key_at;

	if (key == NULL && val == NULL)
	{
		_display_env(*envs);
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
