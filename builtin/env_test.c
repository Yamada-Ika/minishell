#include "test.h"

int	main(void)
{
	t_envvar	*env_var = NULL;
	char		stdout_buf[8192];
	size_t		buf_len = 8192;
	char 		*ex;

	printf("env_test : START!\n\n");

	fflush(stdout);
	bzero(stdout_buf, 8192);
	setbuf(stdout, stdout_buf);
	env(env_var);
	printf("%s\n", stdout_buf);
	ex = "";
	assert(strncmp(stdout_buf, ex, strlen(ex)) == 0);

	fflush(stdout);
	bzero(stdout_buf, 8192);
	setbuf(stdout, stdout_buf);
	export(&env_var, strdup("key"), strdup("val"));
	env(env_var);
	printf("%s\n", stdout_buf);
	ex = "key=val";
	assert(strncmp(stdout_buf, ex, strlen(ex)) == 0);

	delete_envlists(env_var);

	printf("env_test : OK!\n");
}
