#include "minishell.h"

char	*here_doc(char *eos)
{
	char	*str;
	char	*doc;

	doc = ft_strdup("");
	if (doc == NULL)
		error("malloc error");
	while (1)
	{
		write(0, "heredoc>", 8);
		str =  get_next_line(0);
		if (str == NULL)
			error("malloc error");
		if (ft_strncmp(str, eos, ft_strlen(eos)) == 0)
		{
			free(str);
			break;
		}
		doc = ft_strjoin_with_free(&doc, &str);
		if (doc == NULL)
			error("malloc error");
	}
	return (doc);
}


// #include <stdio.h>
// int	main(void)
// {
// 	printf("%s\n",here_doc("EOS"));
// 	return (0);
// }