/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehe <hehe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:52:21 by hehe              #+#    #+#             */
/*   Updated: 2024/10/21 13:52:36 by hehe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_builtins(char *cmd, t_args *arg)
{
	if (arg->delimiter)
		return (1);
	if (ft_strncmp(cmd, "echo", 4) == 1)
		return (1);
	if (ft_strncmp(cmd, "cd", 2) == 1)
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 1)
		return (1);
	if (ft_strncmp(cmd, "export", 6) == 1)
		return (1);
	if (ft_strncmp(cmd, "unset", 5) == 1)
		return (1);
	if (ft_strncmp(cmd, "env", 3) == 1)
		return (1);
	if (ft_strncmp(cmd, "exit", 4) == 1)
		return (1);
	return (0);
}

int	ft_check_builtins_init(char *arg)
{
	if (ft_strncmp(arg, "<<", 2) == 1)
		return (1);
	if (ft_strncmp(arg, "echo", 4) == 1)
		return (1);
	if (ft_strncmp(arg, "cd", 2) == 1)
		return (1);
	if (ft_strncmp(arg, "pwd", 3) == 1)
		return (1);
	if (ft_strncmp(arg, "export", 6) == 1)
		return (1);
	if (ft_strncmp(arg, "unset", 5) == 1)
		return (1);
	if (ft_strncmp(arg, "env", 3) == 1)
		return (1);
	if (ft_strncmp(arg, "exit", 4) == 1)
		return (1);
	return (0);
}
