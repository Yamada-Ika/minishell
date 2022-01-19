#include "minishell.h"

void	pwd_()
{
	char	pathname[512];

	getcwd(pathname, 512); // getcwdはカレントディレクトリ
	printf("%s\n",pathname);
}
