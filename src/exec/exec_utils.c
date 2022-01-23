#include "minishell.h"

char	**_alloc_word_list(t_token *tok, size_t size)
{
	size_t	i;
	size_t	word_list_size;

	word_list_size = 0;
	i = 0;
	while (i < size)
	{
		if (tok->kind == TK_WORD && !is_redirect_kind(tok->prev->kind))
			word_list_size++;
		tok = tok->next;
		i++;
	}
	fprintf(stderr, "***word_list_size : %zu\n", word_list_size);
	return ((char **)ft_calloc(word_list_size + 1, sizeof(char *)));
}

char	**get_command_path(t_envvar *envlist)
{
	char	*val_with_key;
	char	*path_line;
	char	**paths;

	val_with_key = my_getenv(envlist, "PATH");
	if (val_with_key == NULL)
		return (NULL);
	errno = INIT_ERRNO;
	path_line = ft_strdup(val_with_key);
	if (errno != INIT_ERRNO && path_line == NULL)
		error(strerror(errno));
	paths = ft_split(path_line, ':');
	if (errno != INIT_ERRNO && paths == NULL)
		error(strerror(errno));
	free(path_line);
	return (paths);
}

void	handle_fd(int close_fd, int dup_fd, int fd)
{
	close(close_fd);
	if (dup2(dup_fd, fd) == ERROR)
		error(strerror(errno));
	close(dup_fd);
}
