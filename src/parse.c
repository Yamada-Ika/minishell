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

static bool	_is_invalid_redirect(t_token *tok)
{
	if (is_redirect_kind(tok->kind) && (is_redirect_kind(tok->next->kind)
		|| tok->next->kind == TK_OP_PIPE || tok->next->kind == TK_EOF)
	)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token redirection\n", 2);
		return (true);
	}
	return (false);
}

size_t	count_command_size(t_token **tok)
{
	size_t	cnt;

	cnt = 0;
	while ((*tok)->kind != TK_EOF && (*tok)->kind != TK_OP_PIPE)
	{
		if(_is_invalid_redirect(*tok) == true)
			return (0);
		cnt++;
		(*tok) = (*tok)->next;
	}
	return (cnt);
}

t_node	*new_node_command(t_token **tok)
{
	t_node	*node;

	if ((*tok)->kind == TK_EOF || (*tok)->kind == TK_OP_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (NULL);
	}
	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (node == NULL)
		error("parse.c 22 : malloc error");
	node->word_list = *tok;
	node->word_list_size = count_command_size(tok);
	if (node->word_list_size == 0)
	{
		free(node);
		return (NULL);
	}
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

t_node	*parse_error(t_node *node, t_token *token)
{
	free_token_list(token);
	if (node != NULL)
		free_node_list(node);
	return (NULL);
}

t_node	*command_line(t_token **tok)
{
	t_token	*tmp_tk;
	t_token	*tk_head;
	t_node	*node;
	t_node	*tmp_nd;

	tk_head = *tok;
	node = new_node_command(tok);
	if (node == NULL)
		return (parse_error(node, tk_head));
	while ((*tok)->kind == TK_OP_PIPE)
	{
		tmp_tk = *tok;
		*tok = (*tok)->next;
		tmp_nd = new_node_command(tok);
		if (tmp_nd == NULL)
			return (parse_error(node, tk_head));
		node = new_node_pipe(tmp_tk, node, tmp_nd);
	}
	*tok = tk_head;
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
