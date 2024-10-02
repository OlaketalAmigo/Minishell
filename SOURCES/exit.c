/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:46:12 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/02 16:06:41 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(int key)
{
	printf("started builtin exit\n");
	if (key == 1)
	{
		// free all
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_SUCCESS);
}
