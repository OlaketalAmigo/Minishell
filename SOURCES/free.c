/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:06:49 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/24 15:36:29 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_count_check(t_args **arg, int cmd_count)
{
	if (cmd_count == 0 && *arg)
	{
		free(*arg);
		*arg = NULL;
		return (1);
	}
	return (0);
}

void	ft_free_args(char ***args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*args)[i])
	{
		free((*args)[i]);
		i++;
	}
	free(*args);
	*args = NULL;
}

void	ft_free_struct(t_args **arg, int cmd_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmd_count_check(arg, cmd_count) == 1)
		return ;
	while (i < cmd_count)
	{
		if ((*arg)[i].cmd)
		{
			free((*arg)[i].cmd);
			(*arg)[i].cmd = NULL;
		}
		ft_free_args(&(*arg)[i].args);
		i++;
	}
	if (*arg)
	{
		free(*arg);
		*arg = NULL;
	}
}

void	ft_free_all(t_struct *data)
{
	ft_free(data->path);
	ft_free(data->arg);
}

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
