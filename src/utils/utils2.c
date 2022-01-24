#include "minishell.h"

void	ft_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == ERROR)
		error(strerror(errno));
}

int	ft_dup(int fd)
{
	int	duplicated_fd;

	duplicated_fd = dup(fd);
	if (duplicated_fd == ERROR)
		error(strerror(errno));
	return (duplicated_fd);
}

void	ft_pipe(int *fd)
{
	if (pipe(fd) == ERROR)
		error(strerror(errno));
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == ERROR)
		error(strerror(errno));
	return (pid);
}
