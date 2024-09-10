/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:11 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/10 17:58:36 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig_receiver = 0;

void	del(void *content)
{
	free(content);
}

int	main(void)
{
	t_struct	data;
	t_list		*parsing;

	parsing = NULL;
	ft_init_signals();
	while (1)
	{
		g_sig_receiver = 0;
		data.line = readline("MiniHell->");
		if (g_sig_receiver == 1)
			continue ;
		printf("line = %s i\n", data.line);
		if (data.line && data.line[0] != '\0')
		{
			add_history(data.line);
			parsing = ft_parser(&data, parsing);
			ft_exec(parsing);
			ft_free(data.tab);
			ft_free(data.arg);
			free_nodes(&parsing);
			continue ;
		}
		if (g_sig_receiver == 0 && data.line[0] != '\0')
		{
			printf("exit\n");
			break ;
		}
	}
	return (0);
}
