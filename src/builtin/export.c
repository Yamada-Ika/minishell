#include "minishell.h"

static void	get_key_and_val(char **key, char **val, char *str)
{
	size_t		key_len;
	t_envvar	*key_at;
	char		*equal_at;

	if (str[0] == '=')
	{
		*key = ft_strdup("");
		*val = NULL;
		return ;
	}
	equal_at = ft_strchr(str, '=');
	if (equal_at == NULL)
	{
		*key = ft_strdup(str);
		*val = NULL;
		return ;
	}
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
	key_at = get_envvar_with_key(g_mshell.envlist, *key);
	if (key_at != NULL)
		*val = strjoin_and_free(ft_strdup(key_at->val), *val);
}

static void	_export_non_arg(void)
{
	msh_export(&(g_mshell.envlist), NULL, NULL);
	add_exit_status_to_env(0);
}

bool	is_invalid_key(char *key)
{
	size_t	i;

	if (ft_isdigit(key[0]) || key[0] == '\0')
		return (true);
	i = 0;
	while (key[i] != '\0')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (true);
		i++;
	}
	return (false);
}

void	export_(char **args)
{
	size_t		i;
	char		*key;
	char		*val;

	if (args[0] == NULL)
		return (_export_non_arg());
	i = 0;
	while (args[i] != NULL)
	{
		get_key_and_val(&key, &val, args[i]);
		if (is_invalid_key(key))
		{
			error_ident("export", args[i]);
			add_exit_status_to_env(1);
		}
		else
		{
			msh_export(&(g_mshell.envlist), key, val);
			add_exit_status_to_env(0);
			free(key);
			free(val);
		}
		i++;
	}
}

static void	_display_env(t_envvar *envlist)
{
	while (envlist != NULL)
	{
		if (ft_strcmp(envlist->key, "?") != 0)
		{
			if (envlist->val == NULL)
				printf("declare -x %s\n", envlist->key);
			else
				printf("declare -x %s=\"%s\"\n", envlist->key, envlist->val);
		}
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
	else if (val != NULL)
		replace_val(key_at, val);
}
