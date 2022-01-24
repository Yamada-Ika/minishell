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
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishel: exit: ", STDERR_FILENO);
		ft_putstr_fd(num_str, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(255);
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
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
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(0);
	}
	if (i == 2)
		exit_with_num(cmds[1]);
	if (i > 2)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return ;
	}
}

//int	main(int ac, char **av)
//{
//	exit_(av );
//	return (0);
//}
