/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:11 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/10 14:00:14 by gprunet          ###   ########.fr       */
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
		if (data.line)
		{
			add_history(data.line);
			ft_parser(&data, parsing);
			if (parsing && parsing->content)
				printf("parsing = %s\n", parsing->content[0]);
			ft_exec(parsing);
			ft_free(data.arg);
			ft_lstclear(&parsing, *del);
			continue ;
		}
		if (g_sig_receiver == 0)
			break ;
	}
	return (0);
}
