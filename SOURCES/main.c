/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:11 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/06 15:18:56 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig_receiver = 0;

extern char		**environ;

void	heredoc_exit(t_struct *data)
{
	if (data->heredoc == 2)
	{
		close(data->pipefd[0]);
		close(data->saved_stdin);
	}
}

void	ft_main(int g_sig_receiver, t_struct *data)
{
	while (1)
	{
		g_sig_receiver = 0;
		data->line = readline("MiniHell->");
		if (g_sig_receiver != 0)
			continue ;
		if (data->line && data->line[0] != '\0')
		{
			ft_update_history(data->line);
			if (ft_parser(data) < 0)
				continue ;
			ft_exec(data);
			ft_free_all(data);
			free(data->redir);
			continue ;
		}
		if (g_sig_receiver == 0)
		{
			if (data->line && data->line[0] == '\0')
				continue ;
			printf("exit\n");
			heredoc_exit(data);
			break ;
		}
	}
}

int	main(void)
{
	t_struct	data;

	ft_set_up_env(&data, environ);
	ft_set_up_home(&data);
	ft_init_signals();
	ft_set_up_history();
	data.heredoc = 0;
	ft_main(g_sig_receiver, &data);
	ft_final_free(&data);
	return (0);
}
