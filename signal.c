/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:06:44 by iyamada           #+#    #+#             */
/*   Updated: 2022/01/10 22:08:18 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// signal
# include <signal.h>

volatile sig_atomic_t	g_signal;

static void	ft_get_signal(int	signal)
{
	g_signal = signal;
}

int	main(void)
{
	signal(SIGINT, ft_get_signal);
	while (true)
	{
		pause();
		printf("g_signal : %d\n", g_signal);
	}
}
