/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:45:51 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/06 13:22:32 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cleanup(t_struct *data, t_args *arg, int cmd_count)
{
	(void)data;
	if (data->stop == 1)
		printf("syntax error near unexpected token\n");
	if (cmd_count == 0)
		printf("No command to execute\n");
	ft_free_struct(&arg, cmd_count);
}

void	ft_free_struct(t_args **arg, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
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

void	ft_final_free(t_struct *data)
{
	ft_free(data->env);
	if (data->path_to_home)
		free(data->path_to_home);
}
