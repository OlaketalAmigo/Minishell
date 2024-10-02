/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:46:12 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/02 12:10:17 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **args, int key)
{
	printf("started builtin exit\n");
	if (key == 1)
	{
		ft_free(args);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_SUCCESS);
}
