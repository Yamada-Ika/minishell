/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 21:52:59 by iyamada           #+#    #+#             */
/*   Updated: 2022/01/16 22:28:57 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_check_invalid_redirect(t_token *tok)
{
	if (is_redirect_kind(tok->kind) && (is_redirect_kind(tok->next->kind)
		|| tok->next->kind == TK_OP_PIPE || tok->next->kind == TK_EOF)
	)
		error("minishell: syntax error near unexpected token redirection\n");
}

size_t	count_command_size(t_token **tok)
{
	size_t	cnt;

	cnt = 0;
	while ((*tok)->kind != TK_EOF && (*tok)->kind != TK_OP_PIPE)
	{
		_check_invalid_redirect(*tok);
		cnt++;
		(*tok) = (*tok)->next;
	}
	return (cnt);
}

t_node	*new_node_command(t_token **tok)
{
	t_node	*node;

	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (node == NULL)
		error("parse.c 22 : malloc error");
	if ((*tok)->kind == TK_EOF || (*tok)->kind == TK_OP_PIPE)
		error("minishell: syntax error near unexpected token `|'\n");
	node->word_list = *tok;
	node->word_list_size = count_command_size(tok);
	node->kind = ND_CMD;
	return (node);
}

t_node	*new_node_pipe(t_token *token, t_node *left, t_node *right)
{
	t_node	*node;

	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (node == NULL)
		error("parse.c 22 : malloc error");
	node->left = left;
	node->right = right;
	node->kind = ND_PIPE;
	node->word_list = token;
	node->word_list_size = 1;
	return (node);
}


t_node	*command_line(t_token **tok)
{
	t_node	*node;
	t_token	*tmp_tk;
	t_node	*tmp_nd;

	node = new_node_command(tok);
	while ((*tok)->kind == TK_OP_PIPE)
	{
		tmp_tk = *tok;
		*tok = (*tok)->next;
		tmp_nd = new_node_command(tok);
		node = new_node_pipe(tmp_tk, node, tmp_nd);
	}
	return (node);
}

// t_command	*command(t_token **tok)
// {
// 	t_command	*cmd;

// 	cmd = (t_command *)ft_calloc(1, sizeof(t_command));
// 	if (cmd == NULL)
// 		error("parse.c 47 : malloc error");
// 	cmd->word_list = 
// 	return (cmd);
// }
