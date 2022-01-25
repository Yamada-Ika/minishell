#include "minishell.h"

bool	is_exec_with_here_doc(t_command command)
{
	int				fd[2];
	int				sts;
	pid_t			pid;
	t_redirect_list	*last;

	last = _redir_lstlast(command.out_redir);
	if (last && ft_strncmp(last->redirect, "<<", 2) == 0)
	{
		ft_pipe(fd);
		pid = ft_fork();
		if (pid == 0)
		{
			handle_fd(fd[0], fd[1], 1);
			ft_putstr_fd(last->word, 1);
			exit (0);
		}
		else
		{
			handle_fd(fd[1], fd[0], 0);
			waitpid(pid, &sts, 0);
			exec(command.word_list);
		}
	}
	return (false);
}

void	exec(char **cmds)
{
	size_t		i;

	i = 0;
	if (cmds == NULL || cmds[0] == NULL)
		exit(0);
	if (is_exec_built_in_in_child(cmds) == true)
		exit(0);
	if (access(cmds[0], X_OK) == F_OK)
		execve(cmds[0], cmds, NULL);
	if (is_exec_cmd_with_full_path(cmds) == false)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmds[0], 2);
		exit(127);
	}
}

void	exec_t_command(t_command command)
{
	if (handle_in_redir(command.in_redir) == ERROR)
		exit(1);
	if (handle_out_redir(command.out_redir) == ERROR)
		exit(1);
	if (is_exec_with_here_doc(command) == false)
		exec(command.word_list);
}

int	recursive(t_node *node)
{
	pid_t	pid;
	int		fd[2];
	int		sts;

	if (node == NULL )
		return (0);
	ft_pipe(fd);
	pid = ft_fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		handle_fd(fd[1], fd[0], 0);
		if (node->right)
			exec_t_command(node->right->command);
		exec_t_command(node->command);
	}
	else
	{
		handle_fd(fd[0], fd[1], 1);
		if (node->left)
			recursive(node->left);
	}
	waitpid(pid, &sts, 0);
	return (get_exit_status(sts));
}

void	handle_command(t_node *node)
{
	pid_t	pid;
	int		sts;

	signal(SIGINT, back_to_new_prompt);
	if (node->left == NULL && is_exec_built_in(node, node->command) == true)
		return ;
	pid = ft_fork();
	if (pid == 0)
	{
		get_here_doc_form_each_node(node);
		if (g_mshell.interrupt == true)
		{
			g_mshell.interrupt = false;
			exit(1);
		}
		sts = recursive(node);
		exit(sts);
	}
	waitpid(pid, &sts, 0);
	set_exit_status(sts);
}
