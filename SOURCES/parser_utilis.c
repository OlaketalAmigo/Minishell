/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:43:00 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/12 16:22:51 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_parsing(void)
{
	printf("Erreur d'entree\n");
	return ;
}

int	ft_nb_arg(t_struct *data)
{
	int	i;

	i = 0;
	while (data->tmp_arg[i])
		i++;
	return (i);
}