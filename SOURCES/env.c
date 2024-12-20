/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:01:52 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/12/18 13:22:05 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_struct *data)
{
	int		i;

	i = -1;
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], "?=", 2) == 1)
			continue ;
		printf("%s\n", data->env[i]);
	}
	return (0);
}

int	ft_env_pipe(t_struct *data, t_args **arg, char **args, char **path)
{
	int		i;

	i = -1;
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], "?=", 2) == 1)
			continue ;
		printf("%s\n", data->env[i]);
	}
	ft_free_child(args, data, arg, path);
	exit(0);
}
