/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:56:15 by gprunet           #+#    #+#             */
/*   Updated: 2025/01/06 13:07:23 by gprunet          ###   ########.fr       */
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
	if (arg->input)
	{
		fd = check_fd(fd, arg);
		if (fd == -1)
		{
			data->status = 1;
			return (-1);
		}
		post_check_fd(0, data, fd);
	}
	if (arg->output)
	{
		fd = check_fd(fd, arg);
		if (fd == -1)
		{
			data->status = 1;
			return (-1);
		}
		post_check_fd(1, data, fd);
	}
	return (1);
}

int	check_puts2(char *output, char *input, t_args *arg)
{
	if ((*arg).b_input)
	{
		if (!input || (input[0] == '<' && !input[1]))
		{
			printf("syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	if ((*arg).b_output)
	{
		if (!output || (output[0] == '>' && !output[1]))
		{
			printf("syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	return (0);
}

int	check_puts(char *output, char *input, char *cmd, t_args *arg)
{
	if (!input && cmd[0] == '<' && !cmd[1])
	{
		printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (!output && (cmd[0] == '>' && !cmd[1]))
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
		if (check_puts2(output, input, arg))
			return (1);
	}
	return (0);
}

int	redir_cmd(t_args *arg, t_struct *data)
{
	int	fd;

	fd = 0;
	if (arg->input && !arg->cmd)
	{
		fd = open(arg->input, O_RDONLY);
		if (fd < 0)
		{
			perror(arg->input);
			data->status = 1;
			ft_update_return_status(data, data->status);
			return (1);
		}
		close(fd);
	}
	if (!arg->cmd)
		return (1);
	if (check_puts(arg->output, arg->input, arg->cmd, arg))
	{
		data->status = 2;
		ft_update_return_status(data, data->status);
		return (1);
	}
	return (0);
}
