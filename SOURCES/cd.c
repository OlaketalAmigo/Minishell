/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:08:47 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/24 16:43:32 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	int		i;
	char	*path;

	printf("start cd\n");
	i = ft_nb_arg(args);
	if (i == 1)
	{
		path = NULL;
		chdir(path);
		return (1);
	}
	else if (i == 2)
	{
		path = args[1];
		chdir(path);
		return (1);
	}
	else
		printf("cd: string not in pwd: %s\n", args[1]);
	return (-1);
}
