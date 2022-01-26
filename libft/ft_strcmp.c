/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 21:15:14 by iyamada           #+#    #+#             */
/*   Updated: 2022/01/19 16:31:53 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char*s1, const char *s2)
{
	unsigned char	*ss1;
	unsigned char	*ss2;
	size_t 			i;

	i = 0;
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (ss1[i] && ss2[i])
	{
		if (ss1[i] != ss2[i])
			break ;
		i++;
	}
	return (ss1[i] - ss2[i]);
}
