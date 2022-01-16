#include "minishell.h"

static char	**_alloc_word_list(t_token *tok, size_t size)
{
	char	**word_list;
	size_t	i;
	size_t	word_list_size;

	word_list_size = 0;
	i = 0;
	while (i < size)
	{
		if (tok->kind == TK_WORD && !_is_redirect_kind(tok->prev->kind))
			word_list_size++;
		tok = tok->next;
		i++;
	}
	
	return (word_list);
}

// grep -a > file > file2
// word_list[0] = "grep"
// word_list[1] = "-a"
// out_redir -> "file", "file2"
void	create_t_command(t_node *node)
{
	size_t	i;
	t_token	*head;

	head = node->word_list;
	node->command->word_list = _alloc_word_list(head, node->word_list_size);
	i = 0;
	while (i < node->word_list_size)
	{
		
		node->word_list = node->word_list->next;
		i++;
	}
}
