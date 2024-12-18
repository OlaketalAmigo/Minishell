/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:11 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/12/18 15:12:02 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig_receiver = 0;

extern char		**environ;

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
	ft_main(g_sig_receiver, &data);
	ft_final_free(&data);
	return (0);
}
