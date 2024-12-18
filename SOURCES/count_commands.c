/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:47:27 by hehe              #+#    #+#             */
/*   Updated: 2024/12/18 14:31:38 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_struct *data, char *cmd)
{
	if (data->i < data->last - 1)
		perror("Command not found");
	else
		printf("Command %s not found\n", cmd);
}

int	get_count(t_args *arg, int cmd_count)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i <= cmd_count)
	{
		if (arg[i].cmd)
			count = i;
		i = i + 2;
	}
	return (count);
}

int	count_commands(char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}
