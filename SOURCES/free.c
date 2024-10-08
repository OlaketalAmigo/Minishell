/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:06:49 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/03 15:01:50 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cleanup(t_struct *data, t_args *arg, int cmd_count)
{
	if (cmd_count == 0)
		printf("Command %s not found\n", data->arg[0]);
	ft_free_struct(&arg, cmd_count);
}

void	ft_free_args(char ***args)
{
	int	i;

	i = 0;
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

	i = 0;
	if (cmd_count == 0 && *arg)
	{
		free(*arg);
		*arg = NULL;
		return ;
	}
	while (i < cmd_count)
	{
		if ((*arg)[i].cmd != NULL)
			free((*arg)[i].cmd);
		free((*arg)[i].input);
		free((*arg)[i].output);
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
