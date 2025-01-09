/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cmd_utilis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:04:09 by gprunet           #+#    #+#             */
/*   Updated: 2025/01/09 10:23:03 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_fd(int fd, t_args *a)
{
	if (a->m_out > 0 && a->c_out < a->m_out)
	{
		if (a->append)
			fd = open(a->output[a->c_out], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(a->output[a->c_out], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(a->output[a->c_out]);
			return (-1);
		}
		a->c_out++;
	}
	else if (a->m_in > 0 && a->c_in < a->m_in)
	{
		fd = open(a->input[a->c_in], O_RDONLY);
		if (fd < 0)
			return (perror(a->input[a->c_in]), -1);
		a->c_in++;
	}
	if (a->cmd && a->cmd[0] == '>' && a->cmd[1] != '>')
		return (close(fd), -1);
	return (fd);
}

int	check_fds(t_args *arg, t_struct *data)
{
	int	fd;
	int	temp;

	fd = 0;
	temp = arg->m_in - 1;
	if (arg->c_in > 0 || arg->c_out > 0)
		return (0);
	arg->c_out = 1000;
	while (temp >= 0)
	{
		fd = check_fd(fd, arg);
		if (fd < 0)
		{
			data->status = 1;
			arg->stop = 1;
			ft_update_return_status(data, 1);
			return (1);
		}
		close(fd);
		temp--;
	}
	arg->c_in = 0;
	arg->c_out = 0;
	return (0);
}

int	special_case(char *cmd, t_struct *data, char **args, t_args *arg)
{
	if (check_fds(arg, data) == 1)
		return (1);
	if (arg->m_in > 1)
		arg->c_in = arg->m_in - 1;
	if (data->last > 0 && data->i == 0)
	{
		if (ft_strncmp(cmd, "cat", 3) == 1)
		{
			if (args[0] == NULL && arg->m_in == 0 && arg->m_out == 0)
				return (1);
		}
		if (ft_strncmp(cmd, "grep", 4) == 1)
		{
			if (args[0] != NULL)
				return (1);
		}
	}
	return (0);
}
