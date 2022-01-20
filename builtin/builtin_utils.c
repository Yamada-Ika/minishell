#include "libft.h"

void	print_command_usage(char *name, char *usage)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("usage: ", STDERR_FILENO);
	ft_putendl_fd(usage, STDERR_FILENO);
}

void	error_option(char *builtin_name, char *option_name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(builtin_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(option_name, STDERR_FILENO);
	ft_putstr_fd(": invalid option\n", STDERR_FILENO);
}

void	error_ident(char *builtin_name, char *ident)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(builtin_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putchar_fd('`', STDERR_FILENO);
	ft_putstr_fd(ident, STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
}
