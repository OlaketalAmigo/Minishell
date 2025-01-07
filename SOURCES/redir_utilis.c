/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utilis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:37:50 by gprunet           #+#    #+#             */
/*   Updated: 2024/12/18 14:43:25 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_append(char *temp)
{
	if (ft_strstr(temp, ">>") != NULL)
		return (1);
	return (0);
}

int	check_input(t_struct *data, char *temp, t_args *args)
{
	if ((*args).input)
		return (0);
	if (ft_strchr(temp, '<') == 1 && data->redir[0] == 1)
		return (1);
	return (0);
}

int	check_output(t_struct *data, char *temp, t_args *args)
{
	if ((*args).output)
		return (0);
	if (ft_strchr(temp, '>') == 1 && data->redir[0] == 1)
		return (1);
	return (0);
}

int	check_true_redir(t_struct *data, t_args *args, char	*temp)
{
	args->pos_redir = 0;
	while (args->pos_redir < ft_strlen(temp))
	{
		if (temp[args->pos_redir] == '>' || temp[args->pos_redir] == '<')
		{
			if (data->count_redir < data->nb_redir)
			{
				if (data->redir[data->count_redir] == 1)
				{
					data->count_redir++;
					return (1);
				}
				data->count_redir++;
			}
		}
		args->pos_redir++;
	}
	return (0);
}

int	q_redir(t_struct *data, char *temp, t_args *args)
{
	int	i;
	int	count;

	if (check_true_redir(data, args, temp) == 1)
		return (1);
	if (data->nb_redir == 0)
		return (0);
	i = 0;
	count = 0;
	if (check_input(data, temp, args) == 1)
		return (1);
	if (check_output(data, temp, args) == 1)
		return (1);
	if ((*args).output || (*args).input)
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
