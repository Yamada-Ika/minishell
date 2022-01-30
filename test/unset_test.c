#include "test.h"

int	main(void)
{
	t_envvar	*env_var;
	char		stdout_buf[8192];
	size_t		buf_len;
	char		*ex;

	env_var = NULL;
	buf_len = 8192;
	printf("unset_test : START!\n\n");
	fflush(stdout);
	ft_bzero(stdout_buf, 8192);
	setbuf(stdout, stdout_buf);
	msh_export(&env_var, ft_strdup("key"), ft_strdup("val"));
	msh_export(&env_var, ft_strdup("hoge"), ft_strdup("hoge_val"));
	msh_unset(&env_var, "key");
	msh_env(env_var);
	ex = "hoge=hoge_val";
	assert(ft_strncmp(stdout_buf, ex, ft_strlen(ex)) == 0);
	fflush(stdout);
	ft_bzero(stdout_buf, 8192);
	setbuf(stdout, stdout_buf);
	msh_unset(&env_var, "hoge");
	msh_env(env_var);
	ex = "";
	assert(ft_strncmp(stdout_buf, ex, ft_strlen(ex)) == 0);
	delete_envlists(env_var);
	printf("unset_test : OK!\n");
}
