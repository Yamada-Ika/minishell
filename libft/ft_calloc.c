/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:38:13 by tshigena          #+#    #+#             */
/*   Updated: 2022/01/24 16:57:58 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*m_size;
	size_t	product;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	product = count * size;
	if (product / count != size)
	{
		errno = ENOMEM;
		return (NULL);
	}
	m_size = malloc(product);
	if (m_size)
		ft_bzero(m_size, product);
	return (m_size);
}
