#include "envvar.h"

void	add_exit_status_to_env(int status);

static bool	_get_option(char *arg)
{
	if (arg[0] != '-')
		return (false);
	return (is_str_all_c(arg + 1, 'n'));
}

static void	_print_for_echo(char **args, bool opt_n)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		while (opt_n)
		{
			i++;
			opt_n = _get_option(args[i]);
		}
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1] == NULL)
			break ;
		ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
}

void	echo_(char **args)
{
	bool	opt_n;

	if (args[0] == NULL)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		add_exit_status_to_env(0);
		return ;
	}
	opt_n = _get_option(*args);
	_print_for_echo(args, opt_n);
	if (opt_n == false)
		ft_putstr_fd("\n", STDOUT_FILENO);
	add_exit_status_to_env(0);
}
