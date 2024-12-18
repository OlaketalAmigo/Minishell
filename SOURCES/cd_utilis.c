/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utilis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:03:53 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/12/18 11:45:30 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int ft_straight_home(t_struct *data)
{
    char    *path;
    
    path = data->path_to_home;
	if (path)
		chdir(path);
    return (0);
}

void ft_set_up_home(t_struct *data, char **env)
{
    if (env)
    {
        data->path_to_home = ft_get_home(data);
    }
}