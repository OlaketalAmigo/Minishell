/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:15:55 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/12/18 15:42:19 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_sig_receiver;

void	ft_init_signals(void)
{
	signal(SIGINT, ft_get_signal_int);
	signal(SIGQUIT, ft_get_signal_quit);
}

void	ft_get_signal_int(int sig)
{
	(void)sig;
	printf("\n");
	g_sig_receiver = 1;
	ft_handle_signals();
	rl_redisplay();
}

void	ft_get_signal_quit(int sig)
{
	(void)sig;
	g_sig_receiver = 1;
}

void	ft_handle_signals(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
}
