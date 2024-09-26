/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:47:15 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/26 13:24:12 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args)
{
	int		i;

	i = ft_nb_arg(args);
	if (i == 1)
		printf("%s\n", getcwd(NULL, 100));
	else if (i != 1)
	{
		if (args[1][0] == 45)
		{
			printf("pwd: bad option: %s\n", args[1]);
			return (-1);
		}
		else
		{
			printf("pwd: too many arguments\n");
			return (-1);
		}
	}
	return (1);
}
