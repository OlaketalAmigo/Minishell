/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:01:37 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/07 15:30:47 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_max(char **temp, char c, int current)
{
	char 	*full;
	int 	i;
	int 	nb;

	full = ft_strdup("");
	i = 0;
	nb = 0;
	while (current < ft_tablen(temp))
	{
		add_full(temp[current], &full);
		current++;
	}
	while (full[i] && full[i] != '|')
	{
		if (full[i] == c)
			nb++;
		i++;
	}
	free(full);
	return (nb);
}

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
	(*new_args).m_in = get_max(temp, '<', current);
	(*new_args).m_out = get_max(temp, '>', current);
	if (data->n_in == 0)
	{
		free((*new_args).input);
		(*new_args).input = NULL;
	}
	if (data->n_out == 0)
	{
		free((*new_args).output);
		(*new_args).output = NULL;
	}
	return (*new_args);
}

int	c_puts(char **temp, char c, t_struct *data)
{
	int	i;
	int	j;
	int	real_redir;
	int	count;

	i = 0;
	count = 0;
	real_redir = 0;
	while (temp[i])
	{
		j = 0;
		while (temp[i][j])
		{
			if (temp[i][j] == c)
			{
				if (data->redir[count] == 1)
					real_redir++;
				count++;
			}
			j++;	
		}
		i++;
	}
	return (real_redir);
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
		(*new_args)[i].input = malloc(sizeof(char *) * (get_max(temp, '<', i) + 1));
		(*new_args)[i].output = malloc(sizeof(char *) * (get_max(temp, '>', i) + 1));
		(*new_args)[i] = ft_args_init(&(*new_args)[i], data, temp, i);
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

void	ft_exec(t_struct *data)
{
	t_args	*arg;

	data->i = 0;
	data->stop = 0;
	data->heredoc = 0;
	arg = NULL;
	ft_exec_init(data, &arg);
	data->last = get_count(arg, data->total, data);
	while (data->i < data->total && data->stop != 1)
	{
		if (redir_cmd(&arg[data->i], data) == 1)
		{
			data->i++;
			continue ;
		}
		if (pipe_check(data, data->i, data->last, arg[data->i].delimiter) == -1)
			exit(EXIT_FAILURE);
		ft_algo_exec(data, &arg, data->i, data->total);
		reset_pipe_exit(data, data->i, data->last, &arg[data->i]);
		ft_update_return_status(data, data->status);
		data->i++;
	}
	if (data->heredoc == 1 && data->last > 1)
		final_reset(data);
	ft_exec_cleanup(data, arg, data->total);
}
