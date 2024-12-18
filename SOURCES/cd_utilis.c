/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utilis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:03:53 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/12/18 12:55:35 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_straight_home(t_struct *data)
{
	char	*path;

	path = data->path_to_home;
	if (path)
		chdir(path);
	return (0);
}

void	ft_set_up_home(t_struct *data)
{
	char	*tab[3];

	tab[0] = "export";
	tab[1] = "SHLVL=2";
	tab[2] = NULL;
	data->path_to_home = ft_get_home(data);
	ft_export(data, tab);
}
