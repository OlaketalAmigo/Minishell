/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:52:21 by hehe              #+#    #+#             */
/*   Updated: 2024/12/13 14:20:56 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_builtins(char *cmd, t_args *arg)
{
	if (arg->delimiter)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	ft_check_builtins_init(char *arg)
{
	if (ft_strcmp(arg, "<<") == 0)
		return (1);
	if (ft_strcmp(arg, "echo") == 0)
		return (1);
	if (ft_strcmp(arg, "cd") == 0)
		return (1);
	if (ft_strcmp(arg, "pwd") == 0)
		return (1);
	if (ft_strcmp(arg, "export") == 0)
		return (1);
	if (ft_strcmp(arg, "unset") == 0)
		return (1);
	if (ft_strcmp(arg, "env") == 0)
		return (1);
	if (ft_strcmp(arg, "exit") == 0)
		return (1);
	return (0);
}
