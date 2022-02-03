#include "minishell.h"

bool	is_eof_sent(char *read_str)
{
	return (read_str == NULL);
}

void	exit_minishell(void)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(0);
}
