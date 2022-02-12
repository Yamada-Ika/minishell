// #include "envvar.h"
#include "minishell.h"

t_envvar	*new_envlist(char *key, char *val)
{
	t_envvar	*new;

	new = (t_envvar *)ft_calloc(1, sizeof(t_envvar));
	if (new == NULL)
		return (NULL);
	errno = 0;
	new->key = ft_strdup(key);
	new->val = ft_strdup(val);
	if ((new->key == NULL || new->val == NULL) && errno != 0)
		error(strerror(errno));
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
