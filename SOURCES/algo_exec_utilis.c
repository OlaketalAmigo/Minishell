/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_exec_utilis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:21:36 by hehe              #+#    #+#             */
/*   Updated: 2024/12/18 11:54:30 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_stds(t_struct *data, t_args *arg, int i, int last)
{
	if (arg->input || arg->delimiter)
	{
		dup2(data->saved_stdin, 0);
		close(data->saved_stdin);
	}
	if (arg->output)
	{
		dup2(data->saved_stdout, 1);
		close(data->saved_stdout);
	}
	if (data->in_fd != 0 && i == last)
	{
		close(data->in_fd);
		data->in_fd = 0;
	}
	if (data->out_fd != 1 && i == last)
	{
		close(data->out_fd);
		data->out_fd = 1;
	}
}

void	post_algo_free(char **args, char **true_path)
{
	ft_free(args);
	if (true_path)
		ft_free(true_path);
}

int	algo_heredoc(t_struct *data, t_args **arg, int i, int cmd_count)
{
	if ((*arg)[i].delimiter)
	{
		if ((*arg)[i].output)
		{
			dup2(data->saved_stdout, 1);
			close(data->saved_stdout);
		}
		if (ft_heredoc(&(*arg)[i], data) == -1)
			return (-1);
		if (ft_strncmp((*arg)[i].cmd, "<<", 2) == 1)
		{
			if (i == cmd_count - 1)
				reset_stds(data, &(*arg)[i], i, cmd_count);
			return (-1);
		}
		if (i < cmd_count - 1)
			return (-1);
	}
	return (1);
}

int	algo_built(t_struct *data, char **args, char **true_path, t_args **arg)
{
	int	i;

	i = ft_check_function(data, args, true_path, arg);
	// printf("status = %d\n", i);
	data->status = i;
	if (i == -1)
	{
		printf("Command %s not found\n", arg[data->i]->cmd);
		ft_free_child(args, data, arg, data->path);
		return (-1);
	}
	post_algo_free(args, true_path);
	return (i);
}

void	algo_fork(t_struct *data, char **args, char **true_path, t_args **arg)
{
	data->pid = fork();
	if (data->pid == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	else if (data->pid == 0)
		ft_pipe_exec(data, args, true_path, arg);
	else
		waitpid(data->pid, &data->status, 0);
	if (WIFEXITED(data->status))
		data->status = WEXITSTATUS(data->status);
	post_algo_free(args, true_path);
}
