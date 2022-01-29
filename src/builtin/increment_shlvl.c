#include "minishell.h"

void	increment_shlvl(void)
{
	int		shlvl;
	char	*shlvl_val;

	shlvl_val = my_getenv(g_mshell.envlist, "SHLVL");
	if (shlvl_val == NULL)
		return ;
	shlvl = ft_atoi(shlvl_val);
	shlvl_val = ft_itoa(++shlvl);
	msh_export(&(g_mshell.envlist), "SHLVL", shlvl_val);
	free(shlvl_val);
}
