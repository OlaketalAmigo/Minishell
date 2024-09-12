/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:43:00 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/12 15:58:41 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_parsing(void)
{
	printf("Erreur d'entree\n");
	exit(EXIT_FAILURE);
}

int	ft_nb_arg(t_struct *data)
{
	int	i;

	i = 0;
	while (data->tmp_arg[i])
		i++;
	return (i);
}