/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:40:47 by tshigena          #+#    #+#             */
/*   Updated: 2022/01/24 17:00:00 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*cpy;
	size_t	str_size;

	if (src == NULL)
		return (NULL);
	str_size = ft_strlen(src) + 1;
	cpy = (char *)malloc(str_size * sizeof(char));
	if (cpy)
		ft_memcpy(cpy, src, str_size);
	return (cpy);
}
