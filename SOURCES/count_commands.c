/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:47:27 by hehe              #+#    #+#             */
/*   Updated: 2024/10/29 16:41:32 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_commands_utils(char **arg, t_struct *data, int i, int *count)
{
	if (ft_strchr(arg[i], '/') == 1)
	{
		if (ft_check_hard_path(data, arg[i]))
			*count = *count + 1;
	}
	else if (is_empty(arg[i]) == 0)
	{
		if (ft_check_builtins_init(arg[i]) || ft_strchr(arg[i], '|'))
			*count = *count + 1;
		else if (ft_check_path(data, arg[i]))
			*count = *count + 1;
	}
}

int	count_commands(char **arg, t_struct *data)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (i == 0)
		{
			count++;
			i++;
			continue ;
		}
		if (check_redirection_cmd(arg[i]) == 1)
		{
			count++;
			i++;
			continue ;
		}
		count_commands_utils(arg, data, i, &count);
		i++;
	}
	return (count);
}
