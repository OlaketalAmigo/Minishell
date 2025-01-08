/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:47:27 by hehe              #+#    #+#             */
/*   Updated: 2025/01/08 17:56:49 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pos(char *temp, char c, t_args *args)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (temp[i] == c && i == args->pos_redir)
		{
			args->pos_redir++;
			return (1);
		}
		i++;
	}
	return (0);
}

void	print_error(t_struct *data, char *cmd)
{
	if (data->i < data->last - 1)
		perror("Command not found");
	else
		printf("Command %s not found\n", cmd);
}

int	get_count(t_args *arg, int cmd_count, t_struct *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i <= cmd_count)
	{
		if (arg[i].delimiter)
			data->n_heredoc = i;
		if (arg[i].cmd)
			count = i;
		i = i + 2;
	}
	(*arg).c_in = 0;
	(*arg).c_out = 0;
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
