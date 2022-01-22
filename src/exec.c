#include "minishell.h"

int sts;

char	**get_command_path(t_envvar *envlist)
{
	char	*val_with_key;
	char	*path_line;
	char	**paths;

	val_with_key = my_getenv(envlist, "PATH");
	if (val_with_key == NULL)
		return (NULL);
	errno = INIT_ERRNO;
	path_line = ft_strdup(val_with_key);
	if (errno != INIT_ERRNO && path_line == NULL)
		error(strerror(errno));
	paths = ft_split(path_line, ':');
	if (errno != INIT_ERRNO && paths == NULL)
		error(strerror(errno));
	free(path_line);
	return (paths);
}

bool	is_exec_with_here_doc(t_command command)
{
	int				fd[2];
	int				sts;
	pid_t			pid;
	t_redirect_list *last;

	last = _redir_lstlast(command.out_redir);
	if (last && ft_strncmp(last->redirect, "<<", 2) == 0)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			ft_putstr_fd(last->word, 1);
			exit (0);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			waitpid(pid, &sts, 0);
			exec(command.word_list);
		}
	}
	return (false);
}

void exec(char **cmds)
{
	char	*absolute_path;
	char	*cmd;
	char	**paths;
	size_t	i;

	fprintf(stderr, "exec called\n");
	i = 0;
	if (cmds == NULL || cmds[0] == NULL)
		exit (0);
	if(access(cmds[0], X_OK) == F_OK)
		execve(cmds[0], cmds, NULL);
	cmd = ft_strjoin("/", cmds[0]);
	paths = get_command_path(g_mshell->envlist);
	while (paths && paths[i])
	{
		absolute_path = ft_strjoin(paths[i], cmd);
		if (access(absolute_path, X_OK) == F_OK)
		{
			free(cmd);
			execve(absolute_path, cmds, NULL);
		}
		free(absolute_path);
		i++;
	}
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd + 1, 2);
	exit (127);
}

void	exec_t_command(t_command command)
{
	if (is_exec_built_in(NULL, command) == true)
		exit(0);
	if (handle_in_redir(command.in_redir) == ERROR)
		exit (1);
	if (handle_out_redir(command.out_redir) == ERROR)
		exit (1);
	if (is_exec_with_here_doc(command) == false)
		exec(command.word_list);
}

void recursive(t_node *node)
{
	pid_t pid;
	int fd[2];

	if (node->left == NULL )
		exec_t_command(node->command);

	pipe(fd);
	pid = fork();

	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		exec_t_command(node->right->command);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		recursive(node->left);
	}
}

void	handle_command(t_node *node)
{
	pid_t	pid;

	signal(SIGINT, (void *)back_to_new_prompt);
	if (node->left == NULL && is_exec_built_in(node, node->command) == true)
		return ;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, (void *)SIG_DFL);
		get_here_doc_form_each_node(node);
		if (g_mshell->interrupt == true)
		{
			g_mshell->interrupt = false;
			exit(0);
		}
		fprintf(stderr, "recursive : called\n");
		recursive(node);
		return;
	}
	waitpid(pid, &sts, 0);
}
