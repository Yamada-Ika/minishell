/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 21:52:59 by iyamada           #+#    #+#             */
/*   Updated: 2022/01/13 03:35:18 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_command_size(t_token **tok)
{
	size_t	cnt;

	cnt = 0;
	while ((*tok)->kind != TK_EOF && check_op(*tok) != OP_PIPE)
	{
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
	node->command = *tok;
	node->command_size = count_command_size(tok);
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
	node->command = token;
	return (node);
}

t_node	*command_line(t_token **tok)
{
	t_node	*node;
	t_token	*tmp_tk;
	t_node	*tmp_nd;

	node = new_node_command(tok);
	while (check_op(*tok) == OP_PIPE)
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
