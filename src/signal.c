#include "minishell.h"

int	ft_get_signal(int	signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return (0);
}

int	ft_set_signal(int	signal)
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

