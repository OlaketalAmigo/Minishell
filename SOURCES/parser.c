/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:59:25 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/13 13:28:32 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printf_parsing(t_struct *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->arg[i])
	{
		j = 0;
		while (data->arg[i][j])
		{
			printf("%c", data->arg[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}

int	ft_parser(t_struct *data)
{
	int	i;

	if (ft_parser_check(data) == -1)
	{
		ft_error_parsing();
		return (-1);
	}
	data->tmp_arg = ft_split(data->line, '|');
	if (!data->tmp_arg)
		i = 0 ; // A CHANGER
	i = 0;
	data->arg = malloc ((ft_nb_arg(data) + 1) * 8);
	if (data->arg)
	{
		while (data->tmp_arg[i])
		{
			data->arg[i] = ft_strtrim(data->tmp_arg[i], " ");
			free(data->tmp_arg[i]);
			i++;
		}
		free(data->tmp_arg);
		data->arg[i] = NULL;
	}
	return (1);
}
