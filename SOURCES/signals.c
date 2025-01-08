/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:15:55 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/08 17:48:47 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sig_receiver;

void	ft_init_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = ft_get_signal_int;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = ft_get_signal_quit;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	ft_get_signal_int(int sig)
{
	g_sig_receiver = sig;
	write(1, "\n", 1);
	if (rl_done == 0)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_get_signal_quit(int sig)
{
	char	*s;

	g_sig_receiver = sig;
	if (rl_done == 1)
	{
		printf("\033[2D\033[0K");
		printf("Quit (core dumped)\n");
		rl_replace_line("", 0);
	}
	else
	{
		s = ft_strdup(rl_line_buffer);
		if (s)
		{
			printf("\033[2D\033[0K");
			rl_replace_line(s, 0);
			free(s);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	ft_handle_signals(void)
{
	rl_on_new_line();
	rl_redisplay();
}
