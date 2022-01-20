#include <assert.h>
#include "envvar.h"

static char	*_get_val_from_envp(char **env, char *key)
{
	int	i = 0;
	size_t	key_len;

	key = ft_strjoin(key, "=");
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0)
			return (ft_substr(env[i], key_len, ft_strlen(env[i])));
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_envvar	*envs = NULL;
	char		*key;
	char		*val;
	char		*msh_val;
	char		*envp_val;

	printf("START!\n");

	inherite_env_val(&envs, envp);

	key = ft_strdup("hoge");
	envp_val = _get_val_from_envp(envp, key);
	val = my_getenv(envs, key);
	printf("expected : %s result : %s\n", envp_val, val);
	assert(val == envp_val);

	key = ft_strdup("PATH");
	envp_val = _get_val_from_envp(envp, key);
	val = my_getenv(envs, key);
	printf("expected : %s result : %s\n", envp_val, val);
	assert(ft_strcmp(val, envp_val) == 0);

	key = ft_strdup("USER");
	envp_val = _get_val_from_envp(envp, key);
	val = my_getenv(envs, key);
	printf("expected : %s result : %s\n", envp_val, val);
	assert(ft_strcmp(val, envp_val) == 0);

	key = ft_strdup("hoge_key");
	msh_val = ft_strdup("hoge_value");
	msh_export(&envs, key, msh_val);
	val = my_getenv(envs, key);
	printf("expected : %s result : %s\n", msh_val, val);
	assert(ft_strcmp(val, msh_val) == 0);

	key = ft_strdup("hogeeeeei");
	msh_val = ft_strdup("hogeeeeeeeeeei_valueeeee");
	msh_export(&envs, key, msh_val);
	val = my_getenv(envs, key);
	printf("expected : %s result : %s\n", msh_val, val);
	assert(ft_strcmp(val, msh_val) == 0);

	key = "hoge_key";
	msh_val = "hoge_value";
	val = my_getenv(envs, key);
	printf("expected : %s result : %s\n", msh_val, val);
	assert(ft_strcmp(val, msh_val) == 0);

	printf("OK!\n");

	delete_envlists(envs);
}
