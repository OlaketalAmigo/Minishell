/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehe <hehe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:05:50 by gprunet           #+#    #+#             */
/*   Updated: 2025/01/07 23:02:27 by hehe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_fill_args(char *cmds, char **args)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	while (args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	i = 0;
	j = 1;
	if (cmds)
	{
		new_args[i] = ft_strdup(cmds);
		while (args[i])
			new_args[j++] = ft_strdup(args[i++]);
	}
	new_args[j] = NULL;
	return (new_args);
}

void	ft_exec_init(t_struct *data, t_args **arg)
{
	data->last = 0;
	data->count_redir = 0;
	data->temp_fd = -1;
	data->status = 0;
	data->input = 0;
	data->output = 0;
	data->path = ft_split(getenv("PATH"), ':');
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

void	reset_pipe_exit(t_struct *data, int i, int last, t_args *arg)
{
	if (arg->m_in > 1)
	{
		if (arg[data->i].c_in < arg[data->i].m_in)
		{
			arg[data->i].c_in++;
			data->i--;
		}
	}
	else if (arg->m_out > 1)
	{
		if (arg[data->i].c_out < arg[data->i].m_out)
		{
			arg[data->i].c_out++;
			data->i--;
		}
	}
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
