/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:59:25 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/12/13 13:38:28 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printf_parsing(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			printf("%c", tab[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}

void	ft_set_up_struct(t_struct *data)
{
	int	i;

	data->tmp_arg = ft_split(data->line, '|');
	free(data->line);
	if (!data->tmp_arg)
		return ;
	i = 0;
	data->arg = malloc ((ft_nb_arg(data->tmp_arg) + 1) * 8);
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
}

int	ft_parser(t_struct *data)
{
	int	i;

	i = ft_parser_check(data);
	if (i == -1)
	{
		ft_error_parsing();
		ft_update_return_status(data, 1);
		return (-1);
	}
	else if (i == -2)
	{
		ft_update_return_status(data, 0);
		return (-1);
	}
	ft_set_up_struct(data);
	ft_expand(data);
	return (1);
}
