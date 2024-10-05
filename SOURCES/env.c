/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:01:52 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/05 12:49:58 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_struct *data)
{
	int	i;

	i = -1;
	printf("started builtin env\n");
	while (data->env[++i])
	{
		printf("%s\n", data->env[i]);
	}
	return (1);
}

int	ft_env_pipe(t_struct *data, t_args *arg, char **args, char **path)
{
	int	i;

	i = -1;
	printf("started builtin env\n");
	while (data->env[++i])
	{
		printf("%s\n", data->env[i]);
	}
	ft_free_child(args, data, arg, path);
	exit(EXIT_SUCCESS);
}