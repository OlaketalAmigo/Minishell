/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:11 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/27 16:05:42 by tfauve-p         ###   ########.fr       */
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
	int		i;
	int		j;
	
	i = -1;
	j = -1;
	if (environ[0] == NULL)
	{
		ft_set_up_env(&data);
		i = -2;
	}
	else
		data.env = environ;
	while (data.env[++j])
		printf("%s\n", data.env[j]);
	ft_init_signals();
	ft_main(g_sig_receiver, &data);
	if (i == -2)
		ft_free(data.env);
	return (0);
}
