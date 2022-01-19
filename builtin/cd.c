#include "minishell.h"

void	cd_(char **cmds)
{
	char	pathname[512];
	DIR		*dp;
	struct dirent *dirp;

	memset(pathname, '\0', 512); // memsetはバイトメモリブロックのセット

	chdir(cmds[1]);
	printf("\n%s\n",cmds[1]);
	getcwd(pathname, 512); // getcwdはカレントディレクトリ
	printf("\n%s\n",pathname);
}
