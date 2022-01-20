#include "envvar.h"

t_envvar	*new_envlist(char *key, char *val)
{
	t_envvar	*new;

	new = (t_envvar *)calloc(1, sizeof(t_envvar));
	if (new == NULL)
		return (NULL);
	new->key = ft_strdup(key);
	new->val = ft_strdup(val);
	if (new->key == NULL || new->val == NULL)
		exit(1);
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

// 前につけた方が良い（追加した順に取得したら計算量減らせる）
// oldsがNULLだった時にlistnewする責任をここにする
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
