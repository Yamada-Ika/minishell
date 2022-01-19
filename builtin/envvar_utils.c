#include "envvar.h"

t_envvar	*new_envlist(char *key, char *val)
{
	t_envvar	*new;

	new = (t_envvar *)calloc(1, sizeof(t_envvar));
	if (new == NULL)
		return (NULL);
	new->key = key;
	new->val = val;
	return (new);
}

t_envvar	*get_envlistlast(t_envvar *envs)
{
	if (envs == NULL)
		return (NULL);
	while (envs->next != NULL)
		envs = envs->next;
	return (envs);
}

void	add_envlist(t_envvar *olds, t_envvar *new)
{
	t_envvar	*olds_last;

	olds_last = get_envlistlast(olds);
	olds_last->next = new;
}

void	delete_envvar_contents(char *key, char *val)
{
	free(key);
	free(val);
}

void	delete_envvar(t_envvar *env)
{
	delete_envvar_contents(env->key, env->val);
	free(env);
}

void	delete_envlists(t_envvar *env)
{
	t_envvar	*cur;

	while (env != NULL)
	{
		cur = env;
		env = env->next;
		delete_envvar(cur);
	}
}
