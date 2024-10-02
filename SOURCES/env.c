/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:01:52 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/02 11:24:59 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_struct *data, int key)
{
	int	i;

	i = -1;
	printf("started builtin env\n");
	while (data->env[++i])
	{
		printf("%s\n", data->env[i]);
	}
	if (key == 1)
		{
			// FREE ICI
			exit(EXIT_SUCCESS);
		}
	else
		return (1);
}
