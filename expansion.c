#include "minishell.h"

size_t	replace_token(t_token **token, char **str)
{
	t_token **head;

	// fprintf(stderr,"token->str:  %.*s\n", token->len,token->str);
	head = token;
	if (str == NULL)
	{
		(*token)->prev->next = (*token)->next->next;
		(*token)->next->next->prev = (*head)->prev;
		// fprintf(stderr,"token->prev->next->str:  %.*s\n", token->prev->next->len,token->prev->next->str);
		// token->prev->next->prev = token->next->next->prev;
		// token->prev->next->prev = head->prev;
		*token = (*head)->next->next;
		// fprintf(stderr,"token->prev->next->next->str:  %.*s\n", token->prev->next->next->len,token->prev->next->next->str);
		// fprintf(stderr,"token->prev->next->prev->str:  %.*s\n", token->prev->next->prev->len,token->prev->next->prev->str);
		return (2);
	}
	return (0);
}

size_t	expand_token(t_token **token, int op_kind)
{
	char	**str;
	char	*variable_name;

	fprintf(stderr,"expand_token called\n");
	if (op_kind == OP_Dollar)
	{
		variable_name = ft_substr((*token)->next->str, 0, (*token)->next->len);
		fprintf(stderr, "variable_name: %s\n", variable_name);
		str = ft_split(getenv(variable_name), ' ');
		if (errno)
			error(strerror(errno));
		if (str != NULL)
			fprintf(stderr, "str: %s\n", *str);
		return (replace_token(token, str));
	}
	return (0);
}

void	expand_node(t_node *node)
{
	int	op_kind;
	size_t	i;
	t_token	*head;

	head = node->word_list;
	i = 0;
	while (i < node->word_list_size)
	{
		op_kind = check_op(node->word_list);
		if (op_kind != OP_SINGLE_Q && op_kind != OP_DOUBLE_Q && op_kind != OP_Dollar)
			i++;
		else
		{
			if (i == 0)
			{
				i += expand_token(&(node->word_list), op_kind);
				node->word_list_size -= i;
				fprintf(stderr, "word_list-str:  %.*s\n", node->word_list->len, node->word_list->str);
				head = node->word_list;
			}
			else
			{
				i += expand_token(&(node->word_list), op_kind);
				node->word_list_size -= i;
			}
		}
		node->word_list = node->word_list->next;
	}
	node->word_list = head;
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