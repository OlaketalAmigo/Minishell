/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:46:12 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/23 13:01:47 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_struct *data, t_args *arg, char **args, char **path)
{
	ft_free(data->env);
	ft_free(data->arg);
	ft_free(data->path);
	ft_free(args);
	ft_free_struct(&arg, 1);
	exit(EXIT_SUCCESS);
}

int	ft_exit_pipe(t_struct *data, t_args *arg, char **args, char **path)
{
	ft_free_child(args, data, arg, path);
	exit(EXIT_SUCCESS);
}
