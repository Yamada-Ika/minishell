//#include "debug.h"
#include "minishell.h"
//#include "../include/minishell.h"

void	debug_node(t_node *node)
{
	const char *kind[] = {
			"TK_OP_DOUBLE_GR",
			"TK_OP_SINGLE_LS",
			"TK_OP_LS",
			"TK_OP_GR",
			"TK_OP_PIPE",
			"TK_OP_DOLLAR",
			"TK_WORD",
			"TK_WORD_IN_SINGLE_Q",
			"TK_WORD_IN_DOUBLE_Q",
			"TK_EOF",
	};

	while (node != NULL)
	{
		t_token	*head_left;
		size_t i_left = 0;
		head_left = node->word_list;
		while (i_left < node->word_list_size)
		{
			fprintf(stderr, "{node->left:word_list_size:[%3zu] word_list->str:[%15s] word_list->kind:[%15s]}\n",
					node->word_list_size,
					node->word_list->str,
					kind[node->word_list->kind]
			);
			i_left++;
			node->word_list = node->word_list->next;
		}
		node->word_list = head_left;
		if (node->right != NULL)
		{
			t_token	*head_right;
			size_t i_right = 0;
			head_right = node->right->word_list;
			while (i_right < node->right->word_list_size)
			{
				fprintf(stderr, "{node->right:word_list_size:[%3zu] word_list->str:[%15s] word_list->kind:[%15s]}\n",
						node->right->word_list_size,
						node->right->word_list->str,
						kind[node->right->word_list->kind]
				);
				i_right++;
				node->right->word_list = node->right->word_list->next;
			}
			node->right->word_list = head_right;
		}
		node = node->left;
	}
}

void	debug_tokenize(t_token *token)
{
	const char *kind[] = {
			"TK_OP_DOUBLE_GR",
			"TK_OP_SINGLE_LS",
			"TK_OP_LS",
			"TK_OP_GR",
			"TK_OP_PIPE",
			"TK_OP_DOLLAR",
			"TK_WORD",
			"TK_WORD_IN_SINGLE_Q",
			"TK_WORD_IN_DOUBLE_Q",
			"TK_EXP_WORD",
			"TK_EOF",
	};
	while (token->kind != TK_EOF)
	{
		if (token == NULL)
			continue ;
		fprintf(stderr, "{kind:[%20s] is_join_prev:[%1d] str:[%15s] prev->kind:[%20s] prev->str:[%15s]}\n",
				kind[token->kind],
				token->is_join_prev,
				token->str,
				kind[token->prev->kind],
				token->prev->str
		);
		token = token->next;
	}
}

void debug_token(t_token *token, size_t loop_cnt)
{
	const char *kind[] = {
			"TK_OP_DOUBLE_GR",
			"TK_OP_SINGLE_LS",
			"TK_OP_LS",
			"TK_OP_GR",
			"TK_OP_PIPE",
			"TK_OP_DOLLAR",
			"TK_WORD",
			"TK_WORD_IN_SINGLE_Q",
			"TK_WORD_IN_DOUBLE_Q",
			"TK_EOF",
	};
	size_t	i;

	i = 0;
	while (i < loop_cnt)
	{
		if (token == NULL)
		{
			i++;
			continue ;
		}
		fprintf(stderr, "{kind:%s, str:%s, prev->kind:%s, prev->str:%s}\n",
			   kind[token->kind],
			   token->str,
			   kind[token->prev->kind],
			   token->prev->str
		);
		token = token->next;
		i++;
	}
}

 void	_debug_strs(char **strs)
{
	size_t	i = 0;

	while (strs[i])
	{
		fprintf(stderr, "create_t_command : 42 : strs debug : %s\n", strs[i]);
		i++;
	}
}

 void	_debug_redirlist(t_redirect_list *lst)
{
	if (lst == NULL)
		fprintf(stderr, "create_t_command : _debug_redirlist : lst is NULL!!!\n");
	while (lst)
	{
		fprintf(stderr, "create_t_command : 85 : _debug_redirlist : word     : %s\n", lst->word);
		fprintf(stderr, "create_t_command : 85 : _debug_redirlist : redirect : %s\n", lst->redirect);
		lst = lst->next;
	}
}

 void	_debug_command(t_command cmd)
{
	_debug_strs(cmd.word_list);
	fprintf(stderr, "create_t_command : in_redir\n");
	_debug_redirlist(cmd.in_redir);
	fprintf(stderr, "create_t_command : out_redir\n");
	_debug_redirlist(cmd.out_redir);
//	fprintf(stderr, "create_t_command : heredoc\n");
//	_debug_redirlist(cmd.heredoc);
}


