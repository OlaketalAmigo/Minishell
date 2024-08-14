/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:09:20 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/08/13 10:53:26 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_skip_until(char *a, char b, int i)
{
	while (a[i] && a[i] != b)
	{
		i++;
	}
	if (!a[i])
		return (-1);
	else
		return (i);
}

int	ft_parser_check_quotes(t_struct *data)
{
	int	i;

	i = 0;
	while (data->line[i])
	{
		if (data->line[i] == 34 || data->line[i] == 39)
		{
			i = ft_skip_until(data->line, data->line[i], i + 1);
			if (i == -1)
				return (-1);
		}
		i++;
	}
	return (1);
}

int	ft_parser_check_pipe_and(t_struct *data)
{
	int	i;

	i = 0;
	while (data->line[i])
	{
		if (data->line[i] == 38)
			return (-1);
		if (data->line[i] == 124 && data->line[i + 1] == 124)
			return (-1);
		i++;
	}
	return (1);
}

int	ft_parser_check(t_struct *data)
{
	if (ft_parser_check_quotes(data) == -1)
		return (free(data->line), -1);
	if (ft_parser_check_pipe_and(data) == -1)
		return (free(data->line), -1);
	return (1);
}
