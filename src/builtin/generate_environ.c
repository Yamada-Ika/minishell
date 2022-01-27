#include "minishell.h"

static char	*_multi_strdup(char *top, char *mid, char *end)
{
	char	*s;
	char	*tmp_for_free;

	s = ft_strjoin(top, mid);
	tmp_for_free = s;
	s = ft_strjoin(s, end);
	free(tmp_for_free);
	return (s);
}

static size_t	_get_envlist_size(t_envvar *envlist)
{
	size_t		size;

	size = 0;
	while (envlist != NULL)
	{
		if (ft_strcmp(envlist->key, "?") != 0)
			size++;
		envlist = envlist->next;
	}
	return (size);
}

static void	_set_environ_from_envlist(char **envs, t_envvar *envlist)
{
	size_t	i;

	i = 0;
	while (envlist != NULL)
	{
		if (ft_strcmp(envlist->key, "?") != 0)
		{
			envs[i] = _multi_strdup(envlist->key, "=", envlist->val);
			i++;
		}
		envlist = envlist->next;
	}
}

char	**generate_environ(void)
{
	char	**envs;
	size_t	size;

	size = _get_envlist_size(g_mshell.envlist);
	envs = (char **)ft_calloc(size + 1, sizeof(char *));
	if (envs == NULL)
		error(strerror(errno));
	_set_environ_from_envlist(envs, g_mshell.envlist);
	return (envs);
}

// gcc generate_environ.c -I../../include -L../../libft -lft
// t_mshell	g_mshell;

// #include <assert.h>
// int	main(void)
// {
// 	t_envvar	*envlist;
// 	t_envvar	*envlist2;
// 	t_envvar	*envlist3;
// 	char		**envs;
// 	size_t		i;

// 	envlist = malloc(sizeof(t_envvar));
// 	envlist->key = strdup("key1");
// 	envlist->val = strdup("val1");
// 	envlist2 = malloc(sizeof(t_envvar));;
// 	envlist2->key = strdup("key2");
// 	envlist2->val = strdup("val2");
// 	envlist3 = malloc(sizeof(t_envvar));;
// 	envlist3->key = strdup("key3");
// 	envlist3->val = strdup("val3");
// 	envlist->next = envlist2;
// 	envlist2->next = envlist3;

// 	t_envvar *head;
// 	head = envlist;
// 	while (envlist != NULL)
// 	{
// 		fprintf(stderr, "%s=%s\n", envlist->key, envlist->val);
// 		envlist = envlist->next;
// 	}
// 	envlist = head;

// 	g_mshell.envlist = envlist;

// 	head = g_mshell.envlist;
// 	while (g_mshell.envlist != NULL)
// 	{
// 		fprintf(stderr, "%s=%s\n", g_mshell.envlist->key, g_mshell.envlist->val);
// 		g_mshell.envlist = g_mshell.envlist->next;
// 	}
// 	g_mshell.envlist = head;

// 	envs = generate_environ();
// 	assert(strcmp(envs[0], "key1=val1") == 0);
// 	assert(strcmp(envs[1], "key2=val2") == 0);
// 	assert(strcmp(envs[2], "key3=val3") == 0);
// }
