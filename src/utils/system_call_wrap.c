#include "minishell.h"

int	my_dup2(int origin_fd, int copied_fd)
{
	errno = ERRNO_INIT_VAL;
	return (dup2(origin_fd, copied_fd));
}
