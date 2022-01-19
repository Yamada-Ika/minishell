#include "test.h"

int	main(void)
{
	char		stdout_buf[8192];
	size_t		buf_len = 8192;
	char *strs1[] = {"-n", "hoge", NULL};

	printf("echo_test : START!\n\n");

	fflush(stdout);
	ft_bzero(stdout_buf, 8192);
	setbuf(stdout, stdout_buf);
	echo(strs1);
	char	*exp1 = "hoge";
	assert(ft_strncmp(stdout_buf, exp1, ft_strlen(exp1)) == 0);


	char *strs2[] = {"aaa", "bbb", NULL};
	fflush(stdout);
	ft_bzero(stdout_buf, 8192);
	setbuf(stdout, stdout_buf);
	echo(strs2);
	char	*exp2 = "aaa bbb";
	assert(ft_strncmp(stdout_buf, exp2, ft_strlen(exp1)) == 0);

	char *strs3[] = {"ccc", NULL};
	fflush(stdout);
	ft_bzero(stdout_buf, 8192);
	setbuf(stdout, stdout_buf);
	echo(strs3);
	char	*exp3 = "ccc";
	assert(ft_strncmp(stdout_buf, exp3, ft_strlen(exp1)) == 0);

	printf("\necho_test : OK!\n");
}
