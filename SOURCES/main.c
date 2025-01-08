/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:11 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/08 14:25:00 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_receiver = 0;

extern char				**environ;

void	ft_main_mecanism(t_struct *data)
{
	ft_update_history(data->line);
	if (ft_parser(data) < 0)
		return ;
	ft_exec(data);
	ft_free_all(data);
}

void	ft_main(t_struct *data)
{
	while (1)
	{
		if (g_sig_receiver == 2 || g_sig_receiver == 3)
		{
			if (g_sig_receiver == 2)
				ft_update_return_status(data, 130);
			g_sig_receiver = 0;
			continue ;
		}
		data->line = readline("MiniHell->");
		if (data->line && data->line[0] != '\0')
		{
			ft_main_mecanism(data);
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
	ft_main(&data);
	ft_final_free(&data);
	return (0);
}
