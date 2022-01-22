#include "minishell.h"

void	*display_new_prompt(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return (0);
}

int	ft_set_signal(int signal)
{
	if (signal == SIGINT)
	{
		// ft_putchar_fd('\n', 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
	return (0);
}

int	interrupt(int signal)
{
	int fd;
	if (signal == SIGINT)
	{
		g_mshell->interrupt = true;
		fd = dup(0);
		close(0);
//		dup2(fd, 0);
//		close(fd);
	}
	return (0);
}
