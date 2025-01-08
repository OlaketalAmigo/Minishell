/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:01:37 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/08 17:45:33 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_args(char **arg, t_args **new_args, t_struct *data)
{
	int		i;
	char	**temp;

	i = 0;
	*new_args = malloc(sizeof(t_args) * (count_commands(arg) + 1));
	if (!*new_args)
		return (0);
	while (arg[i])
	{
		temp = ft_split_cleared(arg[i], ' ');
		(*new_args)[i].args = malloc(sizeof(char *) * (c_args(temp) + 1));
		if (!(*new_args)[i].args)
			return (0);
		(*new_args)[i].cmd = NULL;
		(*new_args)[i].input = NULL;
		(*new_args)[i].output = NULL;
		(*new_args)[i].delimiter = NULL;
		(*new_args)[i].append = 0;
		(*new_args)[i].pos_redir = 0;
		ft_assign_args(&(*new_args)[i], temp, data);
		ft_free(temp);
		i++;
	}
	return (count_commands(arg));
}

int	handle_redirection(t_args *arg, t_struct *data)
{
	int	fd;

	fd = 0;
	if (data->input)
		close(data->saved_stdin);
	if (arg->input)
	{
		fd = check_fd(fd, arg);
		if (fd == -1)
			return (-1);
		data->saved_stdin = dup(0);
		dup2(fd, 0);
		close(fd);
		data->input = 1;
	}
	if (arg->output)
	{
		fd = check_fd(fd, arg);
		if (fd == -1)
			return (-1);
		data->saved_stdout = dup(1);
		dup2(fd, 1);
		close(fd);
		data->output = 1;
	}
	return (1);
}

void	ft_pipe_exec(t_struct *data, char **args, char **path, t_args **arg)
{
	if (data->pid == 0)
	{
		if (handle_redirection(&(*arg)[data->i], data) == -1)
		{
			ft_free_child(args, data, arg, path);
			exit(EXIT_FAILURE);
		}
		if (data->in_fd != 0 && !(*arg)[data->i].input)
		{
			dup2(data->in_fd, 0);
			close(data->in_fd);
		}
		if (data->out_fd != 1 && !(*arg)[data->i].output)
		{
			dup2(data->out_fd, 1);
			close(data->out_fd);
		}
		data->status = ft_function_pipe(data, args, path, arg);
		if (data->status == -1 || data->status == 127)
		{
			print_error(data, (*arg)[data->i].cmd);
			ft_free_child(args, data, arg, path);
			exit(data->status);
		}
	}
}

void	ft_algo_exec(t_struct *data, t_args **arg, int i, int total)
{
	char	**args;
	char	**true_path;

	args = ft_fill_args((*arg)[i].cmd, (*arg)[i].args);
	true_path = ft_assign_path(data, (*arg)[i].cmd);
	if (handle_redirection(&(*arg)[i], data) == -1)
	{
		post_algo_free(args, true_path);
		return ;
	}
	if (algo_heredoc(data, arg, i, total) == -1)
	{
		post_algo_free(args, true_path);
		return ;
	}
	if (ft_check_builtins((*arg)[i].cmd, &(*arg)[i]) && total == 1)
	{
		if (algo_built(data, args, true_path, arg) == -1)
			return ;
		if (i == data->last)
			reset_stds(data, &(*arg)[i], i, data->last);
		return ;
	}
	algo_fork(data, args, true_path, arg);
	reset_stds(data, &(*arg)[i], i, data->last);
}

void	ft_exec(t_struct *data)
{
	t_args	*arg;

	data->i = 0;
	arg = NULL;
	ft_exec_init(data, &arg);
	data->last = get_count(arg, data->total);
	while (data->i < data->total)
	{
		if (!arg[data->i].cmd)
		{
			data->i++;
			continue ;
		}
		data->input = 0;
		data->output = 0;
		if (pipe_check(data, data->i, data->last) == -1)
			exit(EXIT_FAILURE);
		ft_algo_exec(data, &arg, data->i, data->total);
		reset_pipe_exit(data, data->i, data->last);
		ft_update_return_status(data, data->status);
		data->i++;
	}
	if (data->heredoc == 1 && data->last > 1)
		final_reset(data);
	ft_exec_cleanup(data, arg, data->total);
}
