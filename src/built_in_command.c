#include "minishell.h"

void	pwd_()
{
	char	pathname[512];

	getcwd(pathname, 512); // getcwdはカレントディレクトリ
	printf("%s\n",pathname);
}

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

bool	is_exec_built_in(char **cmds)
{
	fprintf(stderr, "is_exec_built_in called\n");
	if (cmds == NULL)
		error("error: is_exec_built_in");
	if (ft_strncmp(cmds[0], "cd", 2) == 0)
		cd_(cmds);
	if (ft_strncmp(cmds[0], "pwd", 3) == 0)
		pwd_();
}
