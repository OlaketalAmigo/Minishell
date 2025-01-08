/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:40:51 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/05 15:28:02 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_up_data_path(t_struct *data)
{
	char	*pog;
	char	*pag;
	int		i;

	i = -1;
	pog = malloc(5);
	if (!pog)
	{
		data->path = NULL;
		return ;
	}
	pog[0] = 80;
	pog[1] = 65;
	pog[2] = 84;
	pog[3] = 72;
	pog[4] = '\0';
	pag = ft_get_from_env(data, pog);
	data->path = ft_split(pag, ':');
	if (pag)
		free(pag);
}
