#include "minishell.h"

size_t	replace_token(t_token **token, char *str)
{
	size_t	increase_tok_num;
	char	**strs;
	t_token	*tmp;

	if (*str == '\0' || is_str_all_c(str, ' '))
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
	return (increase_tok_num);
}

size_t	expand_token(t_token **token, int op_kind)
{
	char	*expanded_value;

	if (op_kind == TK_OP_DOLLAR)
	{
		expanded_value = expand_str((*token)->str);
		if (expanded_value == NULL)
			error(strerror(errno));
		return (replace_token(token, expanded_value));
	}
	return (0);
}

void	expand_node_word_list(t_node *node)
{
	size_t	cur_index;
	size_t	added_token_size;
	int		op_kind;

	cur_index = 0;
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
}

void	expand_node(t_node *node)
{
	t_token	*head;

	head = node->word_list->prev;
	expand_node_word_list(node);
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
