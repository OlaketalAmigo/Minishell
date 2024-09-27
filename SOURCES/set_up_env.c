/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:44:32 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/27 14:22:42 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_up_env(t_struct *data)
{
	int		i;
	int		j;

	i = open("/etc/environment", O_RDONLY);
	if (i == -1)
	{
		return (-1);
	}
	data->env = malloc (2 * 8);
	data->env[0] = malloc (110 * 8);
	data->env[1] = malloc (8);
	j = read(i, data->env[0], 120);
	if (j == -1)
	{
		close(i);
		ft_free(data->env);
		return (-1);
	}
	data->env[0][j] = '\0';
	data->env[1] = NULL;
	return (1);
}