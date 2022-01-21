#include "builtin.h"

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
	char	*s;

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
		printf("%s", args[i]);
		if (args[i + 1] == NULL)
			break ;
		printf(" ");
		i++;
	}
	if (opt_n == false)
		printf("\n");
}
