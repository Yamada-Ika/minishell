#include "envvar.h"

void	delete_envlists(t_envvar *envlist)
{
	t_envvar	*cur;

	while (envlist != NULL)
	{
		cur = envlist;
		envlist = envlist->next;
		delete_envvar(cur);
	}
}

bool	is_exist_key(t_envvar *envlist, char *key)
{
	if (envlist == NULL || key == NULL)
		return (false);
	while (envlist != NULL)
	{
		if (ft_strcmp(envlist->key, key) == 0)
			return (true);
		envlist = envlist->next;
	}
	return (false);
}

t_envvar	*get_envvar_with_key(t_envvar *envlist, char *key)
{
	if (envlist == NULL || key == NULL)
		return (NULL);
	while (envlist != NULL)
	{
		if (ft_strcmp(envlist->key, key) == 0)
			return (envlist);
		envlist = envlist->next;
	}
	return (NULL);
}

void	replace_val(t_envvar *env, char *val)
{
	env->val = ft_strdup(val);
	if (env->val == NULL)
		exit(1);
}
