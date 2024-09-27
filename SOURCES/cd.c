/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:08:47 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/27 16:24:51 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_home(t_struct *data)
{
	char	*tmp;
	int		i;

	i = -1;
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], "HOME=", 5) == 1)
		{
			tmp = data->env[i];
			return (tmp);
		}
	}
	return (NULL);
}

int	ft_cd(t_struct *data, char **args)
{
	int		i;
	char	*path;

	i = ft_nb_arg(args);
	if (i == 1)
	{
		path = ft_get_home(data);
		if (path)
			chdir(path);
		else
			printf("HOME not set\n");
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
