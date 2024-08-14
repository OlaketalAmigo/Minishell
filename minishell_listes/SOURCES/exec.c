/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:01:37 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/08/14 13:55:36 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_list *parsing)
{
	int			i;
	int			j;

	while (parsing && parsing->content && parsing->next_content)
	{
		i = 0;
		printf("boucle = %d\n", i);
		while (parsing->content[i])
		{
			printf("second while\n");
			j = 0;
			while (parsing->content[i][j])
			{
				printf("third while\n");
				printf("[%c]", parsing->content[i][j]);
				j++;
			}
			i++;
		}
		parsing = parsing->next_content;
	}
}
