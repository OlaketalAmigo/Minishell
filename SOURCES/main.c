/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:11 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/13 16:35:09 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig_receiver = 0;

extern char		**environ;

int	main(void)
{
	t_struct	data;
	t_list		*parsing;

	parsing = NULL;
	data.env = environ;
	ft_init_signals();
	while (1)
	{
		g_sig_receiver = 0;
		data.line = readline("MiniHell->");
		if (g_sig_receiver == 1)
			continue ;
		printf("line = %s\n", data.line);
		if (data.line && data.line[0] != '\0')
		{
			add_history(data.line);
			if (ft_parser(&data) < 0)
				continue ;
			ft_exec(&data);
			//ft_free(data.tab);
			ft_free(data.path);
			ft_free(data.flags);
			ft_free(data.cmds);
			ft_free(data.arg);
			continue ;
		}
		if (g_sig_receiver == 0)
		{
			if (data.line && data.line[0] == '\0')
				continue ;
			printf("exit\n");
			break ;
		}
	}
	return (0);
}
