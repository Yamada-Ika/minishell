#include "minishell.h"

void	display_new_prompt(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// return (signal);
}

void	back_to_new_prompt(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	// return (signal);
}

void	interrupt(int signal)
{
	if (signal == SIGINT)
	{
		g_mshell->interrupt = true;
		close(0);
//		dup2(fd, 0);
//		close(fd);
	}
	// return (0);
}
