/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:01:37 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/08 19:36:33 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	ft_args_init(t_args *new_args, t_struct *data, char **temp, int current)
{
	(*new_args).cmd = NULL;
	(*new_args).delimiter = NULL;
	(*new_args).put = 0;
	(*new_args).b_input = 0;
	(*new_args).b_output = 0;
	(*new_args).append = 0;
	(*new_args).pos_redir = 0;
	(*new_args).c_in = 0;
	(*new_args).c_out = 0;
	(*new_args).stop = 0;
	(*new_args).m_in = get_max(temp, '<', current, data);
	if ((*new_args).m_in < 0)
		(*new_args).m_in = 0;
	(*new_args).m_out = get_max(temp, '>', current, data);
	if ((*new_args).m_out < 0)
		(*new_args).m_out = 0;
	(*new_args).input = malloc(8 * ((*new_args).m_in + 1));
	(*new_args).output = malloc(8 * ((*new_args).m_out + 1));
	init_puts(new_args);
	return (*new_args);
}

int	split_args(char **arg, t_args **new_args, t_struct *data)
{
	int		i;
	char	**temp;

	i = 0;
	*new_args = malloc(sizeof(t_args) * (count_commands(arg) + 1));
	if (!*new_args)
		return (0);
	data->n_in = c_puts(arg, '<', data);
	data->n_out = c_puts(arg, '>', data);
	while (arg[i])
	{
		temp = ft_split_cleared(arg[i], ' ');
		(*new_args)[i].args = malloc(sizeof(char *) * (c_args(temp) + 1));
		if (!(*new_args)[i].args)
			return (0);
		(*new_args)[i] = ft_args_init(&(*new_args)[i], data, arg, i);
		ft_assign_args(&(*new_args)[i], temp, data);
		ft_free(temp);
		i++;
	}
	return (count_commands(arg));
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

	if (i > 0 && data->in_fd == 0 && ft_strcmp((*arg)[i].cmd, "cat") == 0
		&& (*arg)[i].m_in == 0 && (*arg)[i].m_out == 0)
	{
		data->status = 0;
		return ;
	}
	if (handle_redirection(&(*arg)[i], data) == -1)
		return ;
	if (algo_heredoc(data, arg, i, data->last) == -1)
		return ;
	args = ft_fill_args((*arg)[i].cmd, (*arg)[i].args);
	true_path = ft_assign_path(data, (*arg)[i].cmd);
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

void	ft_exec(t_struct *dat)
{
	t_args	*arg;

	dat->i = 0;
	dat->stop = 0;
	dat->heredoc = 0;
	arg = NULL;
	ft_exec_init(dat, &arg);
	dat->last = get_count(arg, dat->total, dat);
	while (dat->i < dat->total && dat->stop == 0)
	{
		if (redir_cmd(&arg[dat->i], dat) == 1)
		{
			dat->i++;
			continue ;
		}
		if (pipe_check(dat, dat->i, dat->last, arg[dat->i].delimiter) == -1)
			exit(EXIT_FAILURE);
		ft_algo_exec(dat, &arg, dat->i, dat->total);
		reset_pipe_exit(dat, dat->i, dat->last, &arg[dat->i]);
		ft_update_return_status(dat, dat->status);
		dat->i++;
	}
	if (dat->heredoc == 1 && dat->last > 1)
		final_reset(dat);
	ft_exec_cleanup(dat, arg, dat->total);
}
