#include "minishell.h"

void	pwd_(void)
{
	char	pathname[512];

	getcwd(pathname, 512);
	printf("%s\n", pathname);
}
