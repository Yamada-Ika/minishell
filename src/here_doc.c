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

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%s\n",here_doc("EOS"));
// 	return (0);
// }
