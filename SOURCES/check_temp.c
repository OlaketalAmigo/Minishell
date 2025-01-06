/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_temp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:39:04 by gprunet           #+#    #+#             */
/*   Updated: 2025/01/06 13:44:45 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_check(char *temp, t_struct *data, int *r_nb, int *nb)
{
	int	i;
	int	last_pos;

	last_pos = 0;
	i = 0;
	while (temp[i])
	{
		if (temp[i] == '>' || temp[i] == '<')
		{
			if (data->redir[*nb] == 1)
			{
				*r_nb = *r_nb + 1;
				last_pos = i;
			}
			*nb = *nb + 1;
		}
		i++;
	}
	if (last_pos != 0 && last_pos != i - 1)
		return (1);
	return (0);
}

int	temp_check(char **temp, t_struct *data)
{
	int	i;
	int	nb;
	int	r_nb;

	i = 0;
	nb = 0;
	r_nb = 0;
	while (temp[i])
	{
		if (single_check(temp[i], data, &r_nb, &nb) == 1)
		{
			data->stop = 1;
			return (1);
		}
		i++;
	}
	if (r_nb > 2)
	{
		data->stop = 1;
		return (1);
	}
	return (0);
}
