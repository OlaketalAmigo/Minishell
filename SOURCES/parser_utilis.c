/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:43:00 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/14 14:19:11 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_parsing(void)
{
	printf("Invalid Input\n");
	return ;
}

int	ft_nb_arg(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
int	ft_check_starting_pipe(t_struct *data)
{
	int	i;

	i = 0;
	while (data->line[i] == 32 && data->line[i] != '\0')
		i++;
	if (data->line[i] == 124)
		return (-1);
	return (0);
}
