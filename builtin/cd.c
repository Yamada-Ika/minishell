#include "minishell.h"

void	cd_(char **cmds)
{
	char			pathname[512];
//	DIR				*dp;

	ft_bzero(pathname, 512);
	chdir(cmds[1]);
	printf("\n%s\n", cmds[1]);
	getcwd(pathname, 512);
	printf("\n%s\n", pathname);
}
