/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:45:51 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/07 16:01:05 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cleanup(t_struct *data, t_args *arg, int cmd_count)
{
	(void)data;
	data->i = data->i - 1;
	if (data->stop == 1 && (arg[data->i].m_in == 0 && arg[data->i].m_out == 0))
		printf("syntax error near unexpected token\n");
	if (cmd_count == 0)
		printf("No command to execute\n");
	ft_free_struct(&arg, cmd_count);
}

void	ft_free_struct(t_args **arg, int cmd_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd_count)
	{
		j = 0;
		free((*arg)[i].cmd);
		while (j < (*arg)[i].m_in)
			free((*arg)[i].input[j++]);
		j = 0;
		while (j < (*arg)[i].m_out)
			free((*arg)[i].output[j++]);
		free((*arg)[i].delimiter);
		free((*arg)[i].input);
		free((*arg)[i].output);
		ft_free((*arg)[i].args);
		i++;
	}
	if (*arg)
		free(*arg);
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
