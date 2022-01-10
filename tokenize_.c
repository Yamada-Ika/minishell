/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:10:14 by iyamada           #+#    #+#             */
/*   Updated: 2022/01/09 19:22:59 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(char *s, t_token_kind kind)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->kind = kind;
	new_token->str = s;
	return (new_token);
}

// s = cmd1 arg1 | cmd2 arg2
// strs = 
// cmd1
// arg1
// |
// cmd2
// arg2
bool	ft_tokenize(char **strs, t_token **token)
{
	size_t	i;
	t_token	*cur;
	t_token	head;

	head.next = NULL;
	cur = &head;
	i = 0;
	while (strs[i])
	{
		if (ft_check_reserved(strs[i]))
		{
			cur->next = ft_new_token(strs[i], TK_RESERVED);
		}
		else if (ft_check_pipe(strs[i]))
		{
			cur->next = ft_new_token(strs[i], TK_PIPE);
		}
		else
		{
			cur->next = ft_new_token(strs[i], TK_STRING);
		}
		if (cur->next == NULL)
			return (false);
		cur = cur->next;
		i++;
	}
	*token = head.next;
	return (true);
}

int	main(int argc, char *argv[])
{
	char	**strs;
	t_token	*token;

	strs = ft_split(argv[1], ' ');
	if (strs == NULL)
		return (0);
	if (!ft_tokenize(strs, &token))
		return (1);
	while (true)
	{
		if (token == NULL)
			break ;
		printf("token->str : %s\n", token->str);
		printf("token->kind : %u\n", token->kind);
		token = token->next;
	}
}
