#include "minishell.h"

void redirect_in_parrent( t_command redir, int *fd)
{
	fd[0] = dup(0);
	fd[1] = dup(1);
	if (redir.in_redir != NULL)
		handle_in_redir(redir.in_redir);
	if (redir.out_redir != NULL)
		handle_out_redir(redir.out_redir);
}

bool	is_exec_built_in(char **cmds, t_command redir)
{
	int	fd[2];

	fprintf(stderr, "is_exec_built_in called\n");
	if (cmds == NULL)
		error("error: is_exec_built_in");
	if (ft_strncmp(cmds[0], "cd", 2) == 0)
	{
		redirect_in_parrent(redir, fd);
		cd_(cmds);
		if (fd[0])
			dup2(fd[0], 0);
		if (fd[1])
			dup2(fd[1], 1);
		return (true);
	}
	if (ft_strncmp(cmds[0], "pwd", 3) == 0)
	{
		redirect_in_parrent(redir, fd);
		pwd_();
		if (fd[0])
			dup2(fd[0], 0);
		if (fd[1])
			dup2(fd[1], 1);
		return (true);
	}
	return (false);
}
