#include "minishell.h"
int redirect_in_parrent( t_command redir, int *fd)
{
	fd[0] = dup(0);
	fd[1] = dup(1);
	if (handle_in_redir(redir.in_redir) == ERROR)
		return (-1);
	if (handle_out_redir(redir.out_redir) == ERROR)
		return (-1);
	return (0);
}

// cmds[0]にはコマンド名が入っている
static void	_exec_builtin_cmd(t_builtin_kind kind, char **cmds)
{
	if (kind == BUILTIN_ECHO)
		echo_(++cmds);
	if (kind == BUILTIN_CD)
		cd_(cmds);
	if (kind == BUILTIN_PWD)
		pwd_();
	if (kind == BUILTIN_EXPORT)
		export_(++cmds);
	if (kind == BUILTIN_UNSET)
		unset_(++cmds);
	if (kind == BUILTIN_ENV)
		env_(++cmds);
	if (kind == BUILTIN_EXIT)
		exit_(cmds);
}

bool	is_exec_built_in(char **cmds, t_command redir)
{
	const void	*builtin[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit",  NULL};
	int	fd[2];
	int	i;

	fprintf(stderr, "is_exec_built_in called\n");
	if (cmds == NULL)
		error("error: is_exec_built_in");
	i = 0;
	while(builtin[i] != NULL)
	{
		if (ft_strcmp(cmds[0], builtin[i]) == 0)
		{
			if (redirect_in_parrent(redir, fd) == ERROR)
				return (true);
			_exec_builtin_cmd(i, cmds);
			if (fd[0])
				dup2(fd[0], 0);
			if (fd[1])
				dup2(fd[1], 1);
			return (true);
		}
		i++;
	}
	return (false);
}
