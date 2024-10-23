/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:01:52 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/23 15:49:05 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_struct *data)
{
	char	*update;
	int		i;

	i = -1;
	while (data->env[++i])
	{
		printf("%s\n", data->env[i]);
	}
	update = "?=0";
	ft_export_update(data, update);
	return (1);
}

int	ft_env_pipe(t_struct *data, t_args *arg, char **args, char **path)
{
	char	*update;
	int		i;

	i = -1;
	while (data->env[++i])
	{
		printf("%s\n", data->env[i]);
	}
	update = "?=0";
	ft_export_update(data, update);
	ft_free_child(args, data, arg, path);
	exit(EXIT_SUCCESS);
}
