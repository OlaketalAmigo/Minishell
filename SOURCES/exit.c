/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:46:12 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/23 15:49:12 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_struct *data, t_args *arg, char **args, char **path)
{
	char	*update;

	ft_free(data->env);
	ft_free(data->arg);
	ft_free(data->path);
	path = NULL;
	ft_free(args);
	ft_free_struct(&arg, 1);
	update = "?=0";
	ft_export_update(data, update);
	exit(EXIT_SUCCESS);
}

int	ft_exit_pipe(t_struct *data, t_args *arg, char **args, char **path)
{
	char	*update;

	update = "?=0";
	ft_export_update(data, update);
	ft_free_child(args, data, arg, path);
	exit(EXIT_SUCCESS);
}
