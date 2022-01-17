#include "minishell.h"

void	sum_up_token_in_quote_helper(t_token *head, t_token *cur, t_node *node)
{
	char	*str;
	char	*quote;
	size_t	len;

	len = cur->str - head->next->str - 1;
	str = ft_substr(head->next->str, 1, len);
	if (*(head->str + head->len) != ' ') // "の前にspaceがあるかないか
	{
		quote = ft_substr(head->str, 0, head->len);
		str = ft_strjoin_with_free(&quote, &str);
	}
	if (*(cur->str + cur->len) != ' ') // "の後ろにspaceがあるかないか
	{
		quote = ft_substr(cur->next->str, 0, cur->next->len);
		str = ft_strjoin_with_free(&str, &quote);
	}
	if (str == NULL)
		error("sum_up_token_in_quote 9 : malloc");
	head->next->str = str;
	fprintf(stderr, "sum_up_token_in_quote_helper : head->next->str : [%s]\n", head->next->str);
}

// token : echo, -n, ",     hoge, ', juga, ', "
// result -> hogejuga
void	sum_up_token_in_quote(t_node *node)
{
	t_token			*head;
	t_token			*tok_before_quote;
	size_t			i;
	size_t			sum_len;
	t_token_kind	quote_kind;

	quote_kind = -1;
	head = node->word_list;
	i = 0;
	while (i < node->word_list_size)
	{
		if (quote_kind == -1 && (node->word_list->kind == TK_OP_SINGLE_Q || node->word_list->kind == TK_OP_DOUBLE_Q))
		{
			sum_len = 0;
			quote_kind = node->word_list->kind;
			tok_before_quote = node->word_list->prev;
		}
		else if (quote_kind == node->word_list->kind)
		{
			quote_kind = -1;
			sum_up_token_in_quote_helper(tok_before_quote, node->word_list, node);
		}
		// else
		// {
		// 	sum_len += node->word_list->len;
		// }
		node->word_list = node->word_list->next;
		i++;
	}
	node->word_list = head;
}


