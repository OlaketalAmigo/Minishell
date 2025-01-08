/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:05:50 by gprunet           #+#    #+#             */
/*   Updated: 2025/01/08 17:58:25 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_init(t_struct *data, t_args **arg)
{
	data->last = 0;
	data->stop = 0;
	data->count_redir = 0;
	data->temp_fd = -1;
	data->status = 0;
	data->input = 0;
	data->output = 0;
	ft_set_up_data_path(data);
	data->in_fd = 0;
	data->out_fd = 1;
	data->pid = 0;
	data->heredoc = 0;
	data->saved_stdin = -1;
	data->saved_stdout = -1;
	data->total = split_args(data->arg, arg, data);
}

void	final_reset(t_struct *data)
{
	if (data->saved_stdin != 0 && data->saved_stdin != -1)
	{
		dup2(data->saved_stdin, 0);
		close(data->saved_stdin);
		data->saved_stdin = -1;
	}
}

int	pipe_check(t_struct *data, int i, int last, char *delimiter)
{
	data->input = 0;
	data->output = 0;
	if (delimiter)
		data->heredoc = 1;
	if (i < last && last > 1)
	{
		if (pipe(data->pipefd) == -1)
		{
			perror("pipe error");
			return (-1);
		}
		data->out_fd = data->pipefd[1];
	}
	else
		data->out_fd = 1;
	return (0);
}

void	update_puts(t_args *arg, t_struct *data)
{
	if (arg->m_in >= 1)
	{
		if (arg->c_in < arg->m_in - 1 || arg->m_in == 1)
		{
			arg->c_in++;
			if (arg->m_in > 1)
				data->i--;
		}
	}
	else if (arg->m_out >= 1)
	{
		if (arg->c_out < arg->m_out - 1 || arg->m_out == 1)
		{
			arg->c_out++;
			if (arg->m_out > 1)
				data->i--;
		}
	}
}

void	reset_pipe_exit(t_struct *data, int i, int last, t_args *arg)
{
	update_puts(arg, data);
	if (i < last)
	{
		if (data->temp_fd != 0 && data->temp_fd != -1)
			close(data->temp_fd);
		data->temp_fd = data->pipefd[0];
		close(data->pipefd[1]);
		data->in_fd = data->pipefd[0];
		if (data->heredoc == 1)
			data->heredoc = 0;
	}
}
