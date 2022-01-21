#include "minishell.h"

int sts;

char	**get_command_path(char **envp)
{
	char *str;

	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH", 4))
		{
			str = ft_strdup(*envp);
			if (str == NULL)
				error(strerror(errno));
			break;
		}
		envp++;
	}
	char **paths = ft_split(str + 5, ':');
		if (paths == NULL)
			error(strerror(errno));
	free(str);
	return (paths);
}

bool	is_exec_with_here_doc(t_command command, char **paths)
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
			exec(paths, command.word_list);
		}
	}
	return (false);
}

void exec(char **paths, char **commands)
{
	char *absolute_path;
	char *command;
	size_t i;

	printf("exec called\n");
	i = 0;
	command = ft_strjoin("/", commands[0]);
	while (paths && paths[i]) {
		absolute_path = ft_strjoin(paths[i], command);
		int ok = access(absolute_path, X_OK);
		if (ok == F_OK)
		{
			free(command);
			execve(absolute_path, commands, NULL);
//			free(absolute_path);
		}
		free(absolute_path);
		i++;
	}
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(command + 1, 2);
	exit (127);
}

void	exec_t_command(t_command command, char **paths)
{
	if (is_exec_built_in(command.word_list, command) == true)
		exit(0);
	if (handle_in_redir(command.in_redir) == ERROR)
		exit (1);
	if (handle_out_redir(command.out_redir) == ERROR)
		exit (1);
	printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
	if (is_exec_with_here_doc(command, paths) == false)
		exec(paths, command.word_list);
}

void recursive(t_node *node, char **paths)
{
	pid_t pid;
	int fd[2];

	if (node->left == NULL )
		exec_t_command(node->command, paths);

	pipe(fd);
	pid = fork();

	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		exec_t_command(node->right->command, paths);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		recursive(node->left, paths);
	}
}

void    handle_command(char **paths, t_node *node)
{
	signal(SIGINT, (void *)ft_set_signal);
	if (node->left == NULL && is_exec_built_in(node->command.word_list, node->command) == true)
		return;
	pid_t pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, (void *)SIG_DFL);
		printf("recursive : called\n");
		recursive(node, paths);
		return;
	}
	waitpid(pid, &sts, 0);
}
