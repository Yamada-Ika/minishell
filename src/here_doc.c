#include "minishell.h"

//void	get_here_doc(char **)
//{
//
//}

//bool	last_is_here_doc(t_redirect_list *last)
//{
//	if (last == NULL)
//		return (false);
//	if (ft_strncmp(last->redirect, "<<", 2) == 0)
//		return (true);
//	return (false);
//}

char	*get_here_doc(char *eos)
{
	char	*str;
	char	*doc;
	char	*eos_n;
	size_t eos_len;

	eos_n = ft_strjoin(eos, "\n");
	free(eos);
	eos_len = ft_strlen(eos_n);
	doc = ft_strdup("");
	if (doc == NULL || eos_n == NULL)
		error("malloc error");
	while (1)
	{
		write(0, "heredoc>", 8);
		str =  get_next_line(0);
		if (str == NULL)
			error("malloc error");
		if (ft_strncmp(str, eos_n, eos_len) == 0)
			break;
		doc = ft_strjoin_with_free(&doc, &str);
		if (doc == NULL)
			error("malloc error");
	}
	free(str);
	free(eos_n);
	return (doc);
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


// #include <stdio.h>
// int	main(void)
// {
// 	printf("%s\n",here_doc("EOS"));
// 	return (0);
// }
