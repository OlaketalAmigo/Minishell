/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehe <hehe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:01:52 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/30 15:20:47 by hehe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_struct *data)
{
	int		i;

	i = -1;
	while (data->env[++i])
	{
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
		printf("%s\n", data->env[i]);
	}
	ft_free_child(args, data, arg, path);
	exit(0);
}
