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
