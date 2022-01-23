#include "envvar.h"

static bool	_get_option(char **args)
{
	if (ft_strcmp(args[0], "-n") == 0)
		return (true);
	return (false);
}

void	echo_(char **args)
{
	bool	opt_n;
	size_t	i;

	if (args[0] == NULL)
	{
		printf("\n");
		return ;
	}
	opt_n = _get_option(args);
	i = 0;
	if (opt_n)
		i = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] == NULL)
			break ;
		ft_putstr_fd(" ", 1);
		i++;
	}
	if (opt_n == false)
		ft_putstr_fd("\n", 1);
}
