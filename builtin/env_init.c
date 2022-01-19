#include "minishell.h"

void	env_init(char **envp)
{
	g_mshell = ft_calloc(1, sizeof(g_mshell));
	inherite_env_val_wrapper(envp);
}
