/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utilis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:37:50 by gprunet           #+#    #+#             */
/*   Updated: 2025/01/07 15:08:22 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_append(char *temp)
{
	if (ft_strstr(temp, ">>") != NULL)
		return (1);
	return (0);
}

int	check_outin(t_struct *data, char *temp, t_args *args, int put)
{
	if (put == 1)
	{
		if ((*args).input[(*args).c_in])
			return (0);
		if (ft_strchr(temp, '<') == 1 && data->redir[0] == 1)
			return (1);
		return (0);
	}
	else
	{
		if ((*args).output[(*args).c_out])
			return (0);
		if (ft_strchr(temp, '>') == 1 && data->redir[0] == 1)
			return (1);
		return (0);
	}
}

void	no_put_case(t_args *args, t_struct *data)
{
	if (data->n_in == 0)
	{
		(*args).input = NULL;
	}
	if (data->n_out == 0)
	{
		(*args).output = NULL;
	}
}

void	init_tab_puts(t_args *args, t_struct *data, int loop)
{
	int	i;

	i = 0;
	if ((data->n_in == 0 || data->n_out == 0) && loop == 0)
		no_put_case(args, data);
	while (i < args->m_in && loop == 0)
	{
		(*args).input[i] = NULL;
		i++;
	}
	i = 0;
	while (i < args->m_out && loop == 0)
	{
		(*args).output[i] = NULL;
		i++;
	}
	if (args->m_in > 0)
	{
		if ((*args).input[(*args).c_in])
			(*args).c_in++;
	}
	if (args->m_out > 0)
	{
		if ((*args).output[(*args).c_out])
			(*args).c_out++;
	}
}

int	check_true_redir(t_struct *data, t_args *args, char	*temp, int i)
{
	init_tab_puts(args, data, i);
	args->pos_redir = 0;
	while (args->pos_redir < ft_strlen(temp))
	{
		if (temp[args->pos_redir] == '>' || temp[args->pos_redir] == '<')
		{
			if (data->count_redir < data->nb_redir)
			{
				if (data->redir[data->count_redir] == 1)
					return (1);
				data->count_redir++;
			}
		}
		args->pos_redir++;
	}
	return (0);
}

int	q_redir(t_struct *data, char *temp, t_args *args, int loop)
{
	int	i;
	int	count;

	if (check_true_redir(data, args, temp, loop) == 1)
		return (1);
	if (data->nb_redir == 0 || data->stop == 0)
		return (0);
	i = 0;
	count = 0;
	if (check_outin(data, temp, args, 1) == 1)
		return (1);
	if (check_outin(data, temp, args, 0) == 1)
		return (1);
	if ((*args).output[(*args).c_out] || (*args).input[(*args).c_in])
	{
		while (temp[i])
		{
			if (temp[i] == '>' || temp[i] == '<')
				count++;
			if (count > 1 && data->redir[count] == 1)
				return (1);
			i++;
		}
	}
	return (0);
}
