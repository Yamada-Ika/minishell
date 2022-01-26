#include "minishell.h"

void	free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
