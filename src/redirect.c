#include "minishell.h"

void	handle_in_redir(t_redirect_list *redirect)
{
	int	fd;

	fprintf(stderr,"handle_in_redir called:  \n");
	if (ft_strncmp(redirect->redirect, ">>", 2) == 0)
		fd = open(redirect->word, O_RDWR | O_APPEND | O_CREAT, 0664);
	else
		fd = open(redirect->word, O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
		error(strerror(errno));
	dup2(fd, 1);
	close(fd);
	if (redirect->next != NULL)
		handle_in_redir(redirect->next);
	else
		fprintf(stderr,"endddddddddddddddddddddddd\n");
}

void	handle_out_redir(t_redirect_list *redirect)
{
	int	fd;

	fprintf(stderr,"handle_out_redir called:  \n");
	if (ft_strncmp(redirect->redirect, "<<", 2))
	{
		fd = open(redirect->word, O_RDONLY);
		if (fd == -1)
			error(strerror(errno));
		dup2(fd, 0);
		close(fd);
	}
	if (redirect->next != NULL)
		handle_out_redir(redirect->next);
}
