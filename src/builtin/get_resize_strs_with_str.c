#include "minishell.h"

static size_t	_get_strs_size_except_str(char **strs, char *s)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	while (strs[i] != NULL)
	{
		if (ft_strcmp(strs[i], s) != 0)
			size++;
		i++;
	}
	return (size);
}

void	_set_newstrs_except_str(char **new,
	size_t new_size, char **old, char *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < new_size)
	{
		if (ft_strcmp(old[i], s) != 0)
		{
			new[j] = ft_strdup(old[i]);
			j++;
		}
		i++;
	}
}

char	**get_resize_strs_with_str(char **strs, char *s)
{
	size_t	new_size;
	char	**new_strs;

	new_size = _get_strs_size_except_str(strs, s);
	new_strs = (char **)ft_calloc(new_size + 1, sizeof(char *));
	_set_newstrs_except_str(new_strs, new_size, strs, s);
	free_strs(strs);
	return (new_strs);
}
