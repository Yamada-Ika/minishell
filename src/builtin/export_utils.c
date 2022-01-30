#include "minishell.h"

bool	is_invalid_key(char *key)
{
	size_t	i;

	if (ft_isdigit(key[0]) || key[0] == '\0')
		return (true);
	i = 0;
	while (key[i] != '\0')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (true);
		i++;
	}
	return (false);
}

void	set_key_and_val(char **key, char **val, char *k, char *v)
{
	if ((k == NULL || v == NULL) && errno)
		error(strerror(errno));
	*key = k;
	*val = v;
}
