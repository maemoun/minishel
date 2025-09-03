/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:28:49 by abdo              #+#    #+#             */
/*   Updated: 2025/08/24 15:56:40 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	g_var = 0;

void	ft_change_global(int flag)
{
	g_var = flag;
}

void	ctld_handler(void)
{
	printf("\033[1A");
	printf("\033[12C");
	printf("exit\n");
	exit(0);
}

void	ctlc_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_var == 0)
		rl_redisplay();
}

void	ft_signals(void)
{
	signal(SIGINT, ctlc_handler);
	signal(SIGQUIT, SIG_IGN);
}
