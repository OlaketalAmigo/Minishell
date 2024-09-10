/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:59:25 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/10 14:02:00 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_final_parsing(t_struct *data, t_list *parsing)
{
	int		i;
	char	**tab;

	i = 0;
	while (data->arg[i])
	{
		tab = ft_split(data->arg[i], 32);
		ft_add_node(&parsing, tab);
		i++;
		ft_free(tab);
	}
	return (parsing);
}

t_list	*ft_parser(t_struct *data, t_list *parsing)
{
	int	i;

	i = 0;
	if (ft_parser_check(data) == -1)
		ft_error_parsing();
	printf("Data->line = %s\n", data->line);
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
	return (ft_final_parsing(data, parsing));
}
