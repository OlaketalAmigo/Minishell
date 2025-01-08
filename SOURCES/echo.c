/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:27:45 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/08 17:45:08 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_first_n_flag(char *tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (tab)
	{
		if (tab[i] == 45)
		{
			i++;
			while (tab[i] == 'n')
			{
				i++;
			}
			if (tab[i] == '\0' && i != 1)
				return (1);
		}
	}
	return (0);
}

int	ft_echo(char **args)
{
	int		option;
	int		i;

	option = 0;
	i = 0;
	while (args[++i])
	{
		if (ft_is_first_n_flag(args[i]) == 1)
		{
			option = 1;
		}
		else
			break ;
	}
	while (args[i])
	{
		printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
	if (option == 0)
		printf("\n");
	return (0);
}

int	ft_echo_pipe(t_struct *data, t_args **arg, char **args, char **path)
{
	int		option;
	int		i;

	option = 0;
	i = 1;
	while (args[++i])
	{
		if (ft_is_first_n_flag(args[i]) == 1)
		{
			option = 1;
		}
		else
			break ;
	}
	while (args[i])
		printf("%s ", args[i++]);
	if (option == 0)
		printf("\n");
	ft_free_child(args, data, arg, path);
	exit(0);
}
