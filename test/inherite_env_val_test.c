#include "test.h"

int	main(int argc, char **argv, char **envp)
{
	t_envvar	*envlist;
	char		stdout_buf[10000];
	size_t		buf_len;
	char		exp[10000];
	char		*tmp_exp;
	char		*tmp;
	size_t		i;

	envlist = NULL;
	buf_len = 10000;
	i = 0;
	printf("inherite_env_val_test : START!\n\n");
	fflush(stdout);
	ft_bzero(stdout_buf, buf_len);
	ft_bzero(exp, buf_len);
	setbuf(stdout, stdout_buf);
	inherite_env_val(&envlist, envp);
	msh_env(envlist);
	tmp = ft_strdup(stdout_buf);
	while (envp[i] != NULL)
	{
		tmp_exp = ft_strjoin(envp[i], "\n");
		ft_strlcat(exp, tmp_exp, ft_strlen(exp) + ft_strlen(tmp_exp) + 1);
		i++;
	}
	assert(ft_strncmp(stdout_buf, exp, ft_strlen(exp)) == 0);
	printf("inherite_env_val_test : OK!\n");
}
