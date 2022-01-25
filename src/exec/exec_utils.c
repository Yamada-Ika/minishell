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
	return ((char **)ft_calloc(word_list_size + 1, sizeof(char *)));
}

char	**get_command_path(t_envvar *envlist)
{
	char	*val_with_key;
	char	*path_line;
	char	**paths;

	errno = ERRNO_INIT_VAL;
	val_with_key = my_getenv(envlist, "PATH");
	if (val_with_key == NULL)
		return (NULL);
	path_line = ft_strdup(val_with_key);
	if (path_line == NULL && errno != ERRNO_INIT_VAL)
		error(strerror(errno));
	errno = ERRNO_INIT_VAL;
	paths = ft_split(path_line, ':');
	if (paths == NULL && errno != ERRNO_INIT_VAL)
		error(strerror(errno));
	free(path_line);
	return (paths);
}

void	handle_fd(int close_fd, int dup_fd, int fd)
{
	close(close_fd);
	ft_dup2(dup_fd, fd);
	close(dup_fd);
}

bool	is_exec_cmd_with_full_path(char **cmds)
{
	char	*absolute_path;
	char	**paths;
	char	*cmd;
	size_t	i;

	i = 0;
	cmd = ft_strjoin("/", cmds[0]);
	paths = get_command_path(g_mshell->envlist);
	if ((cmd == NULL || paths == NULL ) && errno != ERRNO_INIT_VAL)
		error(strerror(errno));
	while (paths && paths[i])
	{
		absolute_path = ft_strjoin(paths[i], cmd);
		if (access(absolute_path, X_OK) == F_OK)
		{
			free(cmd);
			execve(absolute_path, cmds, NULL);
		}
		free(absolute_path);
		i++;
	}
	return (false);
}
