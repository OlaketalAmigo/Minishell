/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:56:15 by gprunet           #+#    #+#             */
/*   Updated: 2025/01/09 12:02:53 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	post_check_fd(int put, t_struct *data, int fd)
{
	if (put == 0)
	{
		if (data->input)
			close(data->saved_stdin);
		data->saved_stdin = dup(0);
		dup2(fd, 0);
		close(fd);
		data->input = 1;
	}
	else
	{
		if (data->output)
			close(data->saved_stdout);
		data->saved_stdout = dup(1);
		dup2(fd, 1);
		close(fd);
		data->output = 1;
	}
}

int	handle_redirection(t_args *arg, t_struct *data)
{
	int	fd;

	fd = 0;
	if (arg->c_out < arg->m_out)
	{
		fd = check_fd(fd, arg);
		if (fd == -1)
		{
			data->status = 1;
			return (-1);
		}
		post_check_fd(1, data, fd);
	}
	if (arg->c_in < arg->m_in)
	{
		fd = check_fd(fd, arg);
		if (fd == -1)
		{
			data->status = 1;
			return (-1);
		}
		post_check_fd(0, data, fd);
	}
	return (1);
}

int	check_puts2(char **out, char **in, t_args *a)
{
	if ((*a).b_input && a->c_in < a->m_in)
	{
		if (!in[a->c_in])
		{
			printf("syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	if ((*a).b_output && a->c_out < a->m_out)
	{
		if (!out[a->c_out])
		{
			printf("syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	return (0);
}

int	check_puts(char *cmd, t_args *arg)
{
	if (arg->m_in > 0 && cmd[0] == '<' && !cmd[1] && arg->input[0])
	{
		printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (arg->m_out > 0 && (cmd[0] == '>' && !cmd[1]) && !arg->output[0])
	{
		printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (!(*arg).delimiter && (cmd[0] == '<' && cmd[1] == '<'))
	{
		printf("synthax error near unexpected token 'newline'\n");
		return (1);
	}
	if ((*arg).put == 1)
	{
		if (check_puts2(arg->output, arg->input, arg))
			return (1);
	}
	return (0);
}

int	redir_cmd(t_args *arg, t_struct *data)
{
	int	fd;

	fd = 0;
	if (arg->c_in > 0 && arg->c_in < arg->m_in && !arg->cmd)
	{
		fd = open(arg->input[arg->c_in], O_RDONLY);
		if (fd < 0 || arg->stop == 1)
		{
			perror(arg->input[arg->c_in]);
			data->status = 1;
			ft_update_return_status(data, data->status);
			return (1);
		}
		close(fd);
	}
	if (special_case(arg->cmd, data, arg->args, arg) || !arg->cmd)
		return (1);
	if (check_puts(arg->cmd, arg))
	{
		data->status = 2;
		ft_update_return_status(data, data->status);
		return (1);
	}
	return (0);
}
