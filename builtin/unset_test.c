#include "test.h"

int	main(void)
{
	t_envvar	*env_var = NULL;
	char		stdout_buf[8192];
	size_t		buf_len = 8192;
	char		*ex;

	printf("unset_test : START!\n\n");

	fflush(stdout);
	bzero(stdout_buf, 8192);
	setbuf(stdout, stdout_buf);
	export(&env_var, strdup("key"), strdup("val"));
	export(&env_var, strdup("hoge"), strdup("hoge_val"));
	unset(&env_var, "key");
	env(env_var);
	ex = "hoge=hoge_val";
	assert(strncmp(stdout_buf, ex, strlen(ex)) == 0);

	fflush(stdout);
	bzero(stdout_buf, 8192);
	setbuf(stdout, stdout_buf);
	unset(&env_var, "hoge");
	env(env_var);
	ex = "";
	assert(strncmp(stdout_buf, ex, strlen(ex)) == 0);

	delete_envlists(env_var);

	printf("unset_test : OK!\n");
}
