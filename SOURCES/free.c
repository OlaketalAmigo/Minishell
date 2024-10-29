/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:06:49 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/29 17:02:47 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cleanup(t_struct *data, t_args *arg, int cmd_count)
{
	(void)data;
	if (cmd_count == 0)
		printf("No command to execute\n");
	ft_free_struct(&arg, cmd_count);
}

void	ft_free_struct(t_args **arg, int cmd_count)
{
	int	i;

	i = 0;
	if (*arg && (*arg)[i].cmd == NULL)
	{
		free(*arg);
		*arg = NULL;
		return ;
	}
	while (i < cmd_count && arg[i])
	{
		if ((*arg)[i].cmd)
		free((*arg)[i].cmd);
		free((*arg)[i].input);
		free((*arg)[i].output);
		free((*arg)[i].delimiter);
		ft_free((*arg)[i].args);
		i++;
	}
	if (*arg)
	{
		free(*arg);
	}
}

void	ft_free_all(t_struct *data)
{
	if (data->path)
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
