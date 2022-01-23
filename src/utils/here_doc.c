#include "minishell.h"

char	*get_here_doc(char *eos)
{
	char	*doc;
	char	*line;
	char	*tmp;
	int		fd;

	fd = dup(0);
	doc = ft_strdup("");
	if (doc == NULL)
		error("malloc error");
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, (void *)interrupt);
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
		{
			if (g_mshell->interrupt == true)
				dup2(fd, 0);
			close(fd);
			return (doc);
		}
		if (ft_strcmp(line, eos) == 0)
			break ;
		tmp = ft_strdup("\n");
		line = ft_strjoin_with_free(&line, &tmp);
		doc = ft_strjoin_with_free(&doc, &line);
		if (doc == NULL)
			error("malloc error");
	}
	free(line);
	return (doc);
}

void	get_here_docs(t_redirect_list *redirect)
{
	while (redirect)
	{
		if (ft_strncmp(redirect->redirect, "<<", 2) == 0)
			redirect->word = get_here_doc(redirect->word);
		if (g_mshell->interrupt == true)
			return ;
		redirect = redirect->next;
	}
}

void	get_here_doc_form_each_node(t_node *node)
{
	while (node->left != NULL)
	{
		get_here_docs(node->right->command.out_redir);
		if (g_mshell->interrupt == true)
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
