#include "minishell.h"

int	handle_in_redir(t_redirect_list *redirect)
{
	int	fd;

	if (redirect == NULL)
		return (0);
	fprintf(stderr,"handle_in_redir called:  \n");
	if (redirect->is_ambiguous == true)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redirect->word, 2);
		ft_putendl_fd(": ambiguous redirect", 2);
		return (-1);
	}
	if (ft_strncmp(redirect->redirect, ">>", 2) == 0)
		fd = open(redirect->word, O_RDWR | O_APPEND | O_CREAT, 0664);
	else
		fd = open(redirect->word, O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (-1);
	}
	dup2(fd, 1);
	close(fd);
	if (redirect->next != NULL)
		handle_in_redir(redirect->next);
	return (0);
}

int	handle_out_redir(t_redirect_list *redirect)
{
	int	fd;

	if (redirect == NULL)
		return (0);
	fprintf(stderr,"handle_out_redir called:  \n");
	if (redirect->is_ambiguous == true)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redirect->word, 2);
		ft_putendl_fd(": ambiguous redirect", 2);
		return (-1);
	}
	if (ft_strncmp(redirect->redirect, "<<", 2))
	{
		fd = open(redirect->word, O_RDONLY);
		if (fd == -1)
		{
			ft_putendl_fd(strerror(errno), 2);
			return (-1);
		}
		dup2(fd, 0);
		close(fd);
	}

	if (redirect->next != NULL)
		handle_out_redir(redirect->next);
	return (0);
}
