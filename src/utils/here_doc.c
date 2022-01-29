#include "minishell.h"

static void	join_here_doc(char *line, char **doc)
{
	if (*doc == NULL)
		*doc = ft_strdup("");
	if (*doc == NULL)
		error(strerror(errno));
	line = strjoin_and_free(line, ft_strdup("\n"));
	*doc = strjoin_and_free_null(doc, &line);
	if (doc == NULL)
		error(strerror(errno));
}

char	*get_here_doc(char *eos)
{
	char	*doc;
	char	*line;
	int		fd;

	fd = ft_dup(0);
	doc = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, interrupt);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			if (g_mshell.interrupt == true)
				ft_dup2(fd, 0);
			close(fd);
			return (doc);
		}
		if (ft_strcmp(line, eos) == 0)
			break ;
		join_here_doc(line, &doc);
	}
	free(line);
	return (doc);
}

void	get_here_docs(t_redirect_list *redirect)
{
	while (redirect)
	{
		if (ft_strcmp(redirect->redirect, "<<") == 0)
			redirect->word = get_here_doc(redirect->word);
		if (g_mshell.interrupt == true)
			return ;
		redirect = redirect->next;
	}
}

void	get_here_doc_form_each_node(t_node *node)
{
	while (node->left != NULL)
	{
		get_here_docs(node->right->command.out_redir);
		if (g_mshell.interrupt == true)
			return ;
		node = node->left;
	}
	get_here_docs(node->command.out_redir);
}

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%s\n",here_doc("EOS"));
// 	return (0);
// }
