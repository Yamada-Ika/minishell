#include "minishell.h"

void	set_exit_status(int status)
{
	if (WTERMSIG(status) == SIGQUIT)
		ft_putendl_fd("Quit: 3", STDERR_FILENO);
	if (WIFSIGNALED(status))
	{
		status = 128 + WTERMSIG(status);
//		printf("signal exit status %d\n", status);
	}
	else
	{
//		printf("other exit status %d\n", WEXITSTATUS(status));
		status = WEXITSTATUS(status);
	}
	add_exit_status_to_env(status);
}

void	add_exit_status_to_env(int status)
{
	char	*status_str;

	status_str = ft_itoa(status);
	if (errno != ERRNO_INIT_VAL && status_str == NULL)
		error(strerror(errno));
	msh_export(&(g_mshell->envlist), "?", status_str);
	free(status_str);
}

int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
	{
		status = 128 + WTERMSIG(status);
		//		printf("signal exit status %d\n", status);
	}
	else
	{
		//		printf("other exit status %d\n", WEXITSTATUS(status));
		status = WEXITSTATUS(status);
	}
	return (status);
}
