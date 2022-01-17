#include "minishell.h"

void	pwd_()
{
	char	pathname[512];

	getcwd(pathname, 512); // getcwdはカレントディレクトリ
	printf("%s\n",pathname);
}

void	cd_(int i, char **cmds)
{
	char	pathname[512];
	DIR		*dp;
	struct dirent *dirp;

	memset(pathname, '\0', 512); // memsetはバイトメモリブロックのセット

	// char path[64] = "./libft";
	chdir(cmds[i]);
	printf("\n%s\n",cmds[i]);
	getcwd(pathname, 512); // getcwdはカレントディレクトリ
	printf("\n%s\n",pathname);

	// dp = opendir(pathname);

	// while ((dirp = readdir(dp)) != NULL)
	//     printf("%s\n", dirp->d_name);

	// closedir(dp);
}
