#include "libft.h"

bool	is_last_char_c(char *str, char c)
{
	size_t	len;

	if (str == NULL || *str == '\0')
		return (false);
	len = ft_strlen(str);
	if (str[len - 1] == c)
		return (true);
	return (false);
}
