/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:01:52 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/02 11:02:22 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_struct *data, int key)
{
	int	i;

	i = -1;
	while (data->env[++i])
	{
		printf("%s\n", data->env[i]);
	}
	if (key == 1)
		{
			// ft_free_child(args, data, )
			exit(EXIT_SUCCESS);
		}
	else
		return (1);
}
