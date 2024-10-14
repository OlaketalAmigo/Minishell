/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:01:37 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/14 17:11:13 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_args(char **arg, t_args **new_args, t_struct *data)
{
	int		i;
	char	**temp;

	i = 0;
	*new_args = malloc(sizeof(t_args) * (count_commands(arg, data) + 1));
	if (!*new_args)
		return (0);
	while (arg[i])
	{
		temp = ft_split_cleared(arg[i], ' ');
		(*new_args)[i].args = malloc(sizeof(char *) * (c_args(temp, data) + 1));
		if (!(*new_args)[i].args)
			return (0);
		(*new_args)[i].cmd = NULL;
		(*new_args)[i].input = NULL;
		(*new_args)[i].output = NULL;
		(*new_args)[i].delimiter = NULL;
		(*new_args)[i].append = 0;
		(*new_args)[i].out = 0;
		(*new_args)[i].in = 0;
		ft_assign_args(&(*new_args)[i], temp, data);
		ft_free(temp);
		i++;
	}
	return (count_commands(arg, data));
}

char	**ft_fill_args(char *cmds, char **args)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	while (args[i] && is_empty(args[i]) == 0)
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

int	handle_redirection(t_args *arg, t_struct *data, char **args)
{
	int	fd;

	if (arg->input)
	{
		fd = open(arg->input, O_RDONLY);
		if (fd < 0)
		{
			perror(arg->input);
			ft_free(args);
			return (-1);
		}
		data->saved_stdin = dup(0);
		dup2(fd, 0);
		close(fd);
	}
	if (arg->output)
	{
		if (arg->append)
			fd = open(arg->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(arg->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(arg->output);
			ft_free(args);
			exit(EXIT_FAILURE);
		}
		data->saved_stdout = dup(1);
		dup2(fd, 1);
		close(fd);
	}
	return (1);
}

void	ft_pipe_exec(t_struct *data, char **args, char **path, t_args *arg)
{
	if (data->pid == 0)
	{
		if (handle_redirection(arg, data, args) == -1)
		{
			ft_free_child(args, data, arg, path);
			exit(EXIT_FAILURE);
		}
		if (data->in_fd != 0 && !arg->input)
		{
			dup2(data->in_fd, 0);
			close(data->in_fd);
		}
		if (data->out_fd != 1 && !arg->output)
		{
			dup2(data->out_fd, 1);
			close(data->out_fd);
		}
		if (ft_check_function_pipe(data, args, path, arg) == -1)
		{
			printf("Ca exit pipe exec ma gueule\n");
			printf("Command %s not found\n", arg->cmd);
			ft_free_child(args, data, arg, path);
			exit(EXIT_FAILURE);
		}
	}
}

void	reset_stds(t_struct *data, t_args *arg, int i, int cmd_count)
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
	if (data->in_fd != 0 && i == cmd_count - 1)
	{
		close(data->in_fd);
		data->in_fd = 0;
	}
	if (data->out_fd != 1 && i == cmd_count - 1)
	{
		close(data->out_fd);
		data->out_fd = 1;
	}
}

void	ft_algo_exec(t_struct *data, t_args *arg, int i, int cmd_count)
{
	char	**args;
	char	**true_path;

	args = ft_fill_args(arg[i].cmd, arg[i].args);
	true_path = ft_assign_path(data, arg[i].cmd);
	if (handle_redirection(&arg[i], data, args) == -1)
	{
		ft_free(args);
		if (true_path)
			ft_free(true_path);
		return ;
	}
	if (arg[i].delimiter)
	{
		if (arg[i].output)
		{
			dup2(data->saved_stdout, 1);
			close(data->saved_stdout);
		}
		if (ft_heredoc(&arg[i], data) == -1)
		{
			perror("heredoc error");
			ft_free(args);
			return ;
		}
		if (ft_strncmp(arg[i].cmd, "<<", 2) == 1)
		{
			if (i == cmd_count - 1)
				reset_stds(data, &arg[i], 0, 0);
			ft_free(args);
			if (true_path)
				ft_free(true_path);
			return ;
		}
	}
	if (ft_check_builtins(arg[i].cmd, &arg[i]) && !arg[i].output)
	{
		if (ft_check_function(data, args, true_path, &arg[i]) == -1)
		{
			printf("Ca exit algo exec ma gueule\n");
			printf("Command %s not found\n", arg[i].cmd);
			ft_free_child(args, data, &arg[i], data->path);
			return ;
		}
		if (i == cmd_count - 1)
			reset_stds(data, &arg[i], 0, 0);
		ft_free(args);
		if (true_path)
			ft_free(true_path);
		return ;
	}
	data->pid = fork();
	if (data->pid == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	else if (data->pid == 0)
		ft_pipe_exec(data, args, true_path, &arg[i]);
	else
		waitpid(data->pid, NULL, 0);
	printf("post exec\n");
	printf("i = %d\n", i);
	reset_stds(data, &arg[i], i, cmd_count);
	ft_free(args);
	if (true_path)
		ft_free(true_path);
}

void	print_struc(t_args arg)
{
	int	i;

	i = 0;
	printf("cmd = %s\n", arg.cmd);
	while (arg.args[i])
	{
		printf("args[%d] = %s\n", i, arg.args[i]);
		i++;
	}
	printf("input = %s\n", arg.input);
	printf("output = %s\n", arg.output);
	printf("delimiter = %s\n", arg.delimiter);
	printf("append = %d\n", arg.append);
}

void	ft_exec(t_struct *data)
{
	int		cmd_count;
	int		i;
	t_args	*arg;

	i = 0;
	cmd_count = 0;
	arg = NULL;
	ft_exec_init(data, &arg, &cmd_count);
	printf("cmd_count = %d\n", cmd_count);
	while (i < cmd_count)
	{
		if (!arg[i].cmd)
		{
			i++;
			continue ;
		}
		print_struc(arg[i]);
		if (i < cmd_count - 1)
		{
			if (pipe(data->pipefd) == -1)
			{
				perror("pipe error");
				exit(EXIT_FAILURE);
			}
			data->out_fd = data->pipefd[1];
		}
		else
			data->out_fd = STDOUT_FILENO;
		ft_algo_exec(data, arg, i, cmd_count);
		if (i < cmd_count - 1)
		{
			close(data->pipefd[1]);
			data->in_fd = data->pipefd[0];
		}
		i++;
	}
	ft_exec_cleanup(data, arg, cmd_count);
}
