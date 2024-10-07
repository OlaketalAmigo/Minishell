/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:59:25 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/07 12:32:25 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printf_parsing(char **tab)
{
	int	i;
	int	j;

	i = 0;
	printf("debut printf tab arg\n");
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
	if (ft_parser_check(data) == -1)
	{
		ft_error_parsing();
		return (-1);
	}
	ft_set_up_struct(data);
	return (1);
}
