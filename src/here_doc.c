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
	char	*doc;
	size_t eos_len;
	char	*line;
	char	*tmp;

	doc = ft_strdup("");
	if (doc == NULL)
		error("malloc error");
	signal(SIGINT, (void *)interrupt);
	while (1)
	{
		if (g_mshell->interrupt == true)
			return (doc);
		line = readline("heredoc> ");
		if (ft_strcmp(line, eos) == 0)
			break;
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
			return;
		redirect = redirect->next;
	}
}

void	get_here_doc_form_each_node(t_node *node)
{
	t_node	*left_node;

	while (node->left != NULL)
	{
		get_here_docs(node->right->command.out_redir);
		if (g_mshell->interrupt == true)
			return;
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
