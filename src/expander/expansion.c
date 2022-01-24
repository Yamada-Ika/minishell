#include "minishell.h"

static size_t	join_valiable(char **p, t_token **tok)
{
	t_token	*cur;
	t_token	head;
	size_t	count;

	count = 0;
	head.next = NULL;
	cur = &head;
	while (p[count])
	{
		cur->next = new_token_tk_word(TK_WORD, p[count], ft_strlen(p[count]));
		cur->next->prev = cur;
		cur = cur->next;
		count++;
	}
	free(p);
	cur->next = (*tok)->next;
	cur->next->prev = cur;
	(*tok)->prev->next = head.next;
	head.next->prev = (*tok)->prev;
	free((*tok)->str);
	free(*tok);
	*tok = cur;
	return (count);
}

size_t	replace_token(t_token **token, char *str)
{
	size_t	increase_tok_num;
	char	**strs;
	t_token	*tmp;

	if (*str == '\0')
	{
		free(str);
		if (is_redirect_kind((*token)->prev->kind))
			return (1);
		 tmp = (*token)->prev;
		 if ((*token)->next->is_join_prev == true)
			 (*token)->next->is_join_prev = false;
		(*token)->prev->next = (*token)->next;
		(*token)->next->prev = (*token)->prev;
		free((*token)->str);
		free((*token));
		*token = tmp;
		return (0);
	}
	strs = ft_split(str, ' ');
	if (strs == NULL)
		 error("expansion.c 153: malloc error");
	free(str);
	increase_tok_num = join_valiable(strs, token);
	debug_token((*token), 1);
	return (increase_tok_num);
}

size_t	expand_token(t_token **token, int op_kind)
{
	char	*expanded_value;

	fprintf(stderr, "expand_token called\n");
	if (op_kind == TK_OP_DOLLAR)
	{
		expanded_value = expand_str((*token)->str);
		if (errno != ERRNO_INIT_VAL)
			error(strerror(errno));
		return (replace_token(token, expanded_value));
	}
	return (0);
}

void	expand_node(t_node *node)
{
	t_token	*head;
	size_t	cur_index;
	size_t	added_token_size;
	int		op_kind;

	head = node->word_list->prev;
	cur_index = 0;
	fprintf(stderr, "word_list_size : %zu cur_index : %zu\n", node->word_list_size, cur_index);
	while (cur_index++ < node->word_list_size)
	{
		op_kind = node->word_list->kind;
		if (op_kind == TK_WORD_IN_SINGLE_Q || op_kind == TK_WORD_IN_DOUBLE_Q)
			handle_token_in_quotes(node->word_list);
		else if (op_kind == TK_OP_DOLLAR)
		{
			added_token_size = expand_token(&(node->word_list), op_kind);
			cur_index += added_token_size - 1;
			node->word_list_size += added_token_size - 1;
		}
		if (node->word_list->is_join_prev == true)
		{
			join_token_and_token_prev(&(node->word_list));
			node->word_list_size -= 1;
			cur_index--;
		}
		node->word_list = node->word_list->next;
	}
	node->word_list = head->next;
	create_t_command(node);
}

void	expansion(t_node *node)
{
	while (node->kind == ND_PIPE)
	{
		expand_node(node->right);
		node = node->left;
	}
	expand_node(node);
}
