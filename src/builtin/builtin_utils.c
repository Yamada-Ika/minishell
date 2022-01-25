#include "libft.h"

#include <string.h>
void	add_exit_status_to_env(int status);

void	print_command_usage2(char *name, char *usage)
{
	ft_putstr_fd("usage: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(" ", STDERR_FILENO);
	ft_putendl_fd(usage, STDERR_FILENO);
}

void	error_option(char *builtin_name, char *option_name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(builtin_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(option_name, STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
}

void	error_option2(char *builtin_name, char option)
{
	ft_putstr_fd(builtin_name, STDERR_FILENO);
	ft_putstr_fd(": illegal option -- ", STDERR_FILENO);
	ft_putchar_fd(option, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	error_with_errno(char *builtin_name, char *arg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(builtin_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	error_ident(char *builtin_name, char *ident)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(builtin_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putchar_fd('`', STDERR_FILENO);
	ft_putstr_fd(ident, STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
	add_exit_status_to_env(1);
}
