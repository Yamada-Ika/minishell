#include "minishell.h"

t_token	*new_token(t_token_kind kind, char *p, size_t len)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		error("malloc error\n");
	token->kind = kind;
	token->str = p;
	token->len = len;
	return (token);
}

size_t get_operator_len(char *p)
{
	const char *kw[] = {"<<", ">>", "<", ">", "|", "'", "\"", NULL};
	size_t  i;

	i = 0;
	while (kw[i] != NULL)
	{
		if (!ft_strncmp(kw[i], p, ft_strlen(kw[i])))
			return (ft_strlen(kw[i]));
		i++;
	}
	return (0);
}

size_t  get_word_len(char *p)
{
	size_t  len;

	len = 0;
	while (!ft_strchr(" ><|'\"", p[len]))
		len++;
	return (len);
}

t_token *tokenize(char *p)
{
	t_token	*cur;
	t_token	head;

	head.next = NULL;
	cur = &head;
	while (*p)
	{
		while (*p == ' ')
			p++;
		if (get_operator_len(p))
		{
			cur->next = new_token(TK_OP, p, get_operator_len(p));
			cur->next->prev = cur;
			cur = cur->next;
			p += cur->len;
			continue;
		}
		if (get_word_len(p))
		{
			cur->next = new_token(TK_WORD, p, get_word_len(p));
			cur->next->prev = cur;
			cur = cur->next;
			p += cur->len;
			continue;
		}
		error("invalid character\n");
	}
	cur->next = new_token(TK_EOF, p, 0);
	cur->next->prev = cur;
	head.next->prev = cur->next;
	return (head.next);
}

void debug_tokenize(t_token *token)
{
	const char *kind[] = {"TK_OP", "TK_WORD", "TK_EOF"};
	while (token->kind != TK_EOF)
	{
		printf("{kind:%s, str:%.*s, prev->kind:%s, prev->str:%.*s}\n", 
			kind[token->kind],
			token->len,
			token->str,
			kind[token->prev->kind],
			token->prev->len,
			token->prev->str
			);
		token = token->next;
	}
}

void	debug_node(t_node *node)
{
	while (node != NULL)
	{
		printf("command_size %zu command->str %.*s\n", 
			node->command_size,
			node->command->len,
			node->command->str
		);
		node = node->left;
	}
}

int	main(int argc, char **argv)
{
	t_token	*token = tokenize(argv[1]);

	// tokenize
	printf("%s\n", token->prev->prev);
	debug_tokenize(token);
	// printf("%.*s\n", token->len, token->str);

	// parse
	t_node	*node = command_line(&token);
	debug_node(node);
}
