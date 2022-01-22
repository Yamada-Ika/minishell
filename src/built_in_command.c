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

bool	is_exec_built_in(t_node *node, t_command redir)
{
	const void	*builtin[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit",  NULL};
	int	fd[2];
	int	i;

	fprintf(stderr, "is_exec_built_in called\n");
	if (redir.word_list == NULL || redir.word_list[0] == NULL)
		return (false);
	i = 0;
	fprintf(stderr, "%p\n", redir.word_list);
	while(builtin[i] != NULL)
	{
		if (ft_strcmp(redir.word_list[0], builtin[i]) == 0)
		{
			if (node != NULL)
				get_here_doc_form_each_node(node);
			if (redirect_in_parrent(redir, fd) != ERROR &&  g_mshell->interrupt == false)
				_exec_builtin_cmd(i, redir.word_list);
			if (fd[0])
				dup2(fd[0], 0);
			if (fd[1])
				dup2(fd[1], 1);
			g_mshell->interrupt = false;
			return (true);
		}
		i++;
	}
	return (false);
}
