/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_args_utilis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:25:18 by gprunet           #+#    #+#             */
/*   Updated: 2024/10/07 12:40:39 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_built(char *temp, t_args *new_args, int *i)
{
	if (ft_check_builtins(temp) == 1 && (*new_args).cmd == NULL)
	{
		(*new_args).cmd = ft_strdup(temp);
		*i = *i + 1;
		return (1);
	}
	return (0);
}

int	check_string(char *temp, int *i)
{
	if (!temp)
		return (0);
	if (ft_strchr(temp, '|') == 1 || is_empty(temp) == 1)
	{
		*i = *i + 1;
		return (1);
	}
	return (0);
}
