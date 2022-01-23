#include "minishell.h"

void	set_exit_status(int status)
{
	char	*status_str;

	errno = INIT_ERRNO;
	status_str = ft_itoa(status);
	fprintf(stderr, "status_error : %s\n", status_str);
	if (errno != INIT_ERRNO && status_str == NULL)
		error(strerror(errno));
	msh_export(&(g_mshell->envlist), "?", status_str);
	free(status_str);
}
