#include "test.h"

int	main(void)
{
	t_envvar	*env_var;
	char		stdout_buf[8192];
	size_t		buf_len;
	char		*ex;

	env_var = NULL;
	buf_len = 8192;
	printf("export_test : START!\n\n");
	fflush(stdout);
	ft_bzero(stdout_buf, 8192);
	setbuf(stdout, stdout_buf);
	msh_export(&env_var, NULL, NULL);
	printf("%s\n", stdout_buf);
	ex = "";
	assert(ft_strncmp(stdout_buf, ex, ft_strlen(ex)) == 0);
	fflush(stdout);
	ft_bzero(stdout_buf, 8192);
	setbuf(stdout, stdout_buf);
	msh_export(&env_var, ft_strdup("key"), ft_strdup("val"));
	msh_export(&env_var, NULL, NULL);
	printf("%s\n", stdout_buf);
	ex = "";
	assert(ft_strncmp(stdout_buf, ex, ft_strlen(ex)) == 0);
	delete_envlists(env_var);
	printf("export_test : OK!\n");
}
