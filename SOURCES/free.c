/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:06:49 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/08 17:58:19 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cleanup(t_struct *data, t_args *arg, int cmd_count)
{
	if (data->i == data->total)
		data->i--;
	if (data->stop == 1 && (arg[data->i].m_in == 0 && arg[data->i].m_out == 0))
		printf("syntax error near unexpected token\n");
	if (data->stop == 1 && ((arg[data->i].m_in > 0 || arg[data->i].m_out > 0)))
	{
		if (arg[data->i].m_in == 1)
			arg[data->i].m_in = 0;
		if (arg[data->i].m_out == 1)
			arg[data->i].m_out = 0;
		ft_update_return_status(data, 2);
		if (arg[data->i].cmd)
		{
			if (arg[data->i].cmd[0] == '>' || arg[data->i].cmd[0] == '<')
				printf("syntax error near unexpected token\n");
		}
		else
			printf("syntax error near unexpected token\n");
	}
	if (arg[data->i].m_in < 0 && data->heredoc == 1)
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
		if ((*arg)[i].m_in > 0)
			ft_free((*arg)[i].input);
		else
			free((*arg)[i].input);
		if ((*arg)[i].m_out > 0)
			ft_free((*arg)[i].output);
		else
			free((*arg)[i].output);
		free((*arg)[i].delimiter);
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
	free(data->redir);
	(void)data;
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
