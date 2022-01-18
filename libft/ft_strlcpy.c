/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:41:07 by tshigena          #+#    #+#             */
/*   Updated: 2022/01/09 15:40:59 by tshigena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i < dstsize)
	{
		if (src[i] == '\0' || dstsize == i + 1)
		{
			dst[i] = '\0';
			break ;
		}
		else
			dst[i] = src[i];
		i++;
	}
	return (ft_strlen(src));
}
