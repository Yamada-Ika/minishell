#include "minishell.h"

static void	_delete_prev_dir(char **dirs)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dirs[i] != NULL)
	{
		if (i == 0 && ft_strcmp(dirs[i], "..") == 0)
		{
			free(dirs[i]);
			dirs[i] = ft_strdup("");
		}
		else if (ft_strcmp(dirs[i], "..") == 0)
		{
			j = i - 1;
			while (true)
			{
				if (dirs[j][0] != '\0')
				{
					free(dirs[j]);
					free(dirs[i]);
					dirs[i] = ft_strdup("");
					dirs[j] = ft_strdup("");
					break ;
				}
				if (j == 0)
				{
					free(dirs[i]);
					dirs[i] = ft_strdup("");
					break ;
				}
				j--;
			}
		}
		i++;
	}
}

static char	*_create_path_line(char **dirs)
{
	size_t	i;
	char	*cano_path;
	char	*tmp;
	char	*str;

	i = 0;
	cano_path = ft_strdup("");
	while (dirs[i] != NULL)
	{
		if (dirs[i][0] == '\0' && i >= 1)
		{
			i++;
			continue ;
		}
		str = ft_strjoin("/", dirs[i]);
		tmp = cano_path;
		cano_path = ft_strjoin(cano_path, str);
		free(str);
		free(tmp);
		i++;
	}
	return (cano_path);
}

char	*get_canonical_path(char *abs_path)
{
	char	**strs;
	char	*path_line;

	if (abs_path == NULL)
		return (NULL);
	strs = ft_split(abs_path, '/');
	// _debug_strs(strs);
	strs = get_resize_strs_with_str(strs, ".");
	_delete_prev_dir(strs);
	// _debug_strs(strs);
	path_line = _create_path_line(strs);
	free_strs(strs);
	return (path_line);
}
