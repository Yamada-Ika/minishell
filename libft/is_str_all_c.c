#include "libft.h"

bool	is_str_all_c(char *str, char c)
{
	while (*str)
	{
		if (*str != c)
			return (false);
		str++;
	}
	return (true);
}
