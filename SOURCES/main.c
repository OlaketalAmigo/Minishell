/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:11 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/02 16:41:42 by gprunet          ###   ########.fr       */
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
		if (g_sig_receiver == 1)
			continue ;
		if (data->line && data->line[0] != '\0')
		{
			add_history(data->line);
			if (ft_parser(data) < 0)
				continue ;
			ft_exec(data);
			ft_free_all(data);
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
	//int			i;

	//i = -1;
	data.launched_env = 0;
	if (environ[0] == NULL)
	{
		ft_set_up_env(&data);
		data.launched_env = 1;
	}
	else
		data.env = environ;
	// while (data.env[++i])
	// 	printf("%s", data.env[i]);
	ft_init_signals();
	ft_main(g_sig_receiver, &data);
	if (data.launched_env == 1)
		ft_free(data.env);
	return (0);
}
