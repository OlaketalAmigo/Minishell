/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:11 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/12 15:48:34 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig_receiver = 0;

void	del(void *content)
{
	free(content);
}

int	main(int argv, char **argc, char **env)
{
	t_struct	data;
	t_list		*parsing;

	parsing = NULL;
	data.env = env;
	(void)argc;
	(void)argv;
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
			ft_parser(&data);
			//ft_exec(parsing, &data);
			//ft_free(data.tab);
			ft_free(data.arg);
			//ft_free(data.path);
			continue ;
		}
		if (g_sig_receiver == 0)
		{
			printf("exit\n");
			break ;
		}
	}
	return (0);
}
