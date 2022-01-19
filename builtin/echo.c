#include "builtin.h"

static bool	_get_option(char **args)
{
	if (ft_strcmp(args[0], "-n") == 0)
		return (true);
	return (false);
}

void	echo(char **args)
{
	bool	flag_n;
	size_t	i;
	char	*s;

	flag_n = _get_option(args);
	i = 0;
	if (flag_n)
		i = 1;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1] == NULL)
			break ;
		printf(" ");
		i++;
	}
	if (flag_n)
		printf("\n");
}
