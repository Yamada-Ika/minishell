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

void exec(char **paths, char **commands) {

	char *absolute_path;
	char *command;
	size_t i;

	i = 0;
	if (ft_strncmp(commands[0], "cd", 2) == 0)
	{
		cd_(1, commands);
		exit(0);
	}
	if (ft_strncmp(commands[0], "pwd", 3) == 0)
	{
		pwd_();
		exit(0);
	}
	else
	command = ft_strjoin("/", commands[0]);
	while (paths[i]) {
		absolute_path = ft_strjoin(paths[i], command);
		int ok = access(absolute_path, X_OK);
		if (ok == F_OK)
		{
			// call(absolute_path, commands);
			execve(absolute_path, commands, NULL);
			free(absolute_path);
			break;
		}
		free(absolute_path);
		i++;
	}
	if (paths[i] == NULL) {
		// printf("minishell: command not found: %s\n", command + 1);
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(command + 1, 2);
	}
	free(command);
}

void recursive(t_node *node, char **paths)
{
	pid_t pid;
	int fd[2];

	if (node->left == NULL )
	{
		if (node->command.in_redir != NULL)
			handle_in_redir(node->command.in_redir);
		if (node->command.out_redir != NULL)
			handle_out_redir(node->command.out_redir);
		t_redirect_list *last = _redir_lstlast(node->command.out_redir);
		fprintf(stderr,"last->word : %s, redirect %s\n", last->word, last->redirect);
		if (last_is_here_doc(last))
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				close(fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
				ft_putstr_fd(last->word, 1);
			}
			else
			{
				close(fd[1]);
				dup2(fd[0], 0);
				close(fd[0]);
				waitpid(pid, &sts, 0);
				exec(paths, node->command.word_list);
			}
		}
		else
			exec(paths, node->command.word_list);
		return;
	}

	pipe(fd);
	pid = fork();

	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		if (node->right->command.in_redir != NULL)
			handle_in_redir(node->right->command.in_redir);
		if (node->right->command.out_redir != NULL)
			handle_out_redir(node->right->command.out_redir);
		exec(paths, node->right->command.word_list);
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
	pid_t pid = fork();
	if (pid == 0)
	{
		// here =  here_doc("EOS");
		signal(SIGQUIT, (void *)SIG_DFL);
		recursive(node, paths);
		return;
	}
	waitpid(pid, &sts, 0);
}
