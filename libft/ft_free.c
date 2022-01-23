#include "libft.h"

void	ft_free(void **p1, void **p2)
{
	if (p1)
	{
		free(*p1);
		*p1 = NULL;
	}
	if (p2)
	{
		free(*p2);
		*p2 = NULL;
	}
}
