#include "minishell.h"

static char	**_alloc_word_list(t_token *tok, size_t size)
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

static t_redirect_list	*_new_redir_list(char *word, char *redirct)
{
	t_redirect_list	*new;

	new = (t_redirect_list *)ft_calloc(1, sizeof(t_redirect_list));
	if (new == NULL && errno)
		error(strerror(errno));
	new->word = word;
	new->redirect = redirct;
	return (new);
}

static void	_redir_lstadd_back(t_redirect_list **lst, t_redirect_list *new)
{
	t_redirect_list	*lst_last;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		lst_last = _redir_lstlast(*lst);
		lst_last->next = new;
	}
	else
		*lst = new;
}

static void	_add_back_redir_list(t_redirect_list **redir_list, t_token *tok)
{
	t_redirect_list	*new;
//	if (tok->kind == TK_OP_SINGLE_LS)
//		tok->next->str = get_here_doc(tok->next->str);
	new = _new_redir_list(tok->next->str, tok->str);
	if (tok->next->kind != TK_WORD)
		new->is_ambiguous = true;
	if (*redir_list == NULL)
		*redir_list = new;
	else
		_redir_lstadd_back(redir_list, new);
}

static void	_add_redir_list(t_node *node, t_token *tok)
{
	if (tok->kind == TK_OP_GR || tok->kind == TK_OP_DOUBLE_GR) // > or >>
		_add_back_redir_list(&node->command.in_redir, tok);
	if (tok->kind == TK_OP_LS || tok->kind == TK_OP_SINGLE_LS) // <
		_add_back_redir_list(&node->command.out_redir, tok);
}

void	create_t_command(t_node *node)
{
	size_t	i;
	size_t	word_list_i;
	t_token	*tok;

	tok = node->word_list;
	node->command.word_list = _alloc_word_list(tok, node->word_list_size);
	if (node->command.word_list == NULL && errno)
		error(strerror(errno));
	word_list_i = 0;
	i = 0;
	while (i < node->word_list_size)
	{
		if (is_redirect_kind(tok->kind))
		{
			_add_redir_list(node, tok);
			tok = tok->next;
			i++;
		}
		else if (tok->kind == TK_WORD)
			node->command.word_list[word_list_i++] = tok->str;
		tok = tok->next;
		i++;
	}
	_debug_command(node->command);
}
