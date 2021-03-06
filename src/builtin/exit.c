#include "minishell.h"

static bool	is_zero(char *num)
{
	if (num == NULL)
		return (false);
	while (*num)
	{
		if (*num != '0')
			return (false);
		num++;
	}
	return (true);
}

void	exit_with_num(char *num_str)
{
	int	num;

	num = ft_atoi_simple(num_str);
	if (num == 0 && is_zero(num_str) == false)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("minishel: exit: ", STDERR_FILENO);
		ft_putstr_fd(num_str, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(255);
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(num);
}

void	exit_(char **cmds)
{
	size_t	i;

	i = 0;
	while (cmds[i])
		i++;
	if (i == 1)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(0);
	}
	if (i == 2)
		exit_with_num(cmds[1]);
	if (i > 2)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (add_exit_status_to_env(1));
	}
}

//int	main(int ac, char **av)
//{
//	exit_(av );
//	return (0);
//}
