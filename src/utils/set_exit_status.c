#include "minishell.h"

void	set_exit_status(int status)
{
	char	*status_str;

	if (WIFSIGNALED(status))
	{
		status = 128 + WTERMSIG(status);
		printf("signal exit status %d\n", status);
	}
	else
	{
		printf("other exit status %d\n", WEXITSTATUS(status));
		status = WEXITSTATUS(status);
	}
	errno = ERRNO_INIT_VAL;
	status_str = ft_itoa(status);
	if (errno != ERRNO_INIT_VAL && status_str == NULL)
		error(strerror(errno));
	msh_export(&(g_mshell->envlist), "?", status_str);
	free(status_str);
}
