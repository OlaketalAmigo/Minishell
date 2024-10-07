/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:46:12 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/07 12:31:20 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_struct *data, t_args *arg, char **args, char **path)
{
	int	i;

	i = 1;
	if (data)
		if (arg)
			if (args)
				if (path)
					i = 4;
	printf("faut free monsieur %d", i);
	printf("started builtin exit\n");
	//Free les trucs avant
	exit(EXIT_SUCCESS);
}

int	ft_exit_pipe(t_struct *data, t_args *arg, char **args, char **path)
{
	printf("started builtin exit\n");
	ft_free_child(args, data, arg, path);
	exit(EXIT_SUCCESS);
}
