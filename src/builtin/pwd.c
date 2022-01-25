#include "minishell.h"

void	pwd_(void)
{
	printf("%s\n", g_mshell.pwd);
	add_exit_status_to_env(0);
}
