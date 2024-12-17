/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:15:55 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/08/07 16:50:27 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig_receiver;

void	ft_init_signals(void)
{
	signal(SIGINT, ft_get_signal_int);
	signal(SIGQUIT, ft_get_signal_quit);
}

void	ft_get_signal_int(int sig)
{
	g_sig_receiver = sig;
	ft_handle_signals();
}

void	ft_get_signal_quit(int sig)
{
	g_sig_receiver = sig;
	close(STDIN_FILENO);
	// write(2, "Quit (core dumped)\n", 19);
	write(STDOUT_FILENO, "\n", 1);
}

void	ft_handle_signals(void)
{
	// ioctl(STDIN_FILENO, TIOCSTI, "\n");
	// rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
