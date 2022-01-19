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

static size_t	ft_max(size_t num1, size_t num2)
{
	if (num1 > num2)
		return (num1);
	return (num2);
}

int	ft_strcmp(const char*s1, const char *s2)
{
	size_t	longer_len;

	longer_len = ft_max(ft_strlen(s1), ft_strlen(s2));
	return (ft_strncmp(s1, s2, longer_len));
}
