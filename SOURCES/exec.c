/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:01:37 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/01 20:23:47 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	ft_args_init(t_args *new_args)
{
	(*new_args).cmd = NULL;
	(*new_args).input = NULL;
	(*new_args).output = NULL;
	(*new_args).delimiter = NULL;
	(*new_args).put = 0;
	(*new_args).b_input = 0;
	(*new_args).b_output = 0;
	(*new_args).append = 0;
	(*new_args).pos_redir = 0;
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
	while (arg[i])
	{
		temp = ft_split_cleared(arg[i], ' ');
		(*new_args)[i].args = malloc(sizeof(char *) * (c_args(temp) + 1));
		if (!(*new_args)[i].args)
			return (0);
		(*new_args)[i] = ft_args_init(&(*new_args)[i]);
		ft_assign_args(&(*new_args)[i], temp, data);
		ft_free(temp);
		i++;
	}
	return (count_commands(arg));
}

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

int	check_puts2(char *output, char *input, t_args *arg)
{
	if ((*arg).b_input)
	{
		if (!input || (input[0] == '<' && !input[1]) 
			|| (input[0] == '>' && !input[1]))
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

void	reset_redir(int *in, int *out)
{
	*in = 0;
	*out = 0;
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
		if (redir_cmd(&arg[data->i], data) == 1)
		{
			data->i++;
			continue ;
		}
		reset_redir(&data->input, &data->output);
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
