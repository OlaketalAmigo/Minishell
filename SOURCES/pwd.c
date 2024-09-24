/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:47:15 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/24 16:42:54 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args)
{
	int		i;
	char	*cwd;

	i = ft_nb_arg(args);
	printf("i = %d\n", i);
	cwd = NULL;
	if (i == 1)
		printf("%s\n", getcwd(cwd, 100));
	else if (i != 1)
	{
		if (args[1][0] == 45)
		{
			printf("bad option: %s\n", args[1]);
			return (-1);
		}
		else
		{
			printf("too many arguments\n");
			return (-1);
		}
	}
	return (1);
}
