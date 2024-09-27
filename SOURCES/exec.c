/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:01:37 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/27 12:10:13 by gprunet          ###   ########.fr       */
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
		int	j = 0;
		while (temp[j])
		{
			printf("temp[%d] = %s\n", j, temp[j]);
			j++;
		}
		(*new_args)[i].args = malloc(sizeof(char *) * (c_args(temp, data) + 1));
		if (!(*new_args)[i].args)
			return (0);
		(*new_args)[i].cmd = NULL;
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

void	ft_pipe_exec(t_struct *data, char **args, char **path, t_args *arg)
{
	if (data->pid == 0)
	{
		printf("debut pipe exec\n");
		if (data->in_fd != 0)
		{
			printf("fermeture in_fd\n");
			dup2(data->in_fd, 0);
			close(data->in_fd);
		}
		if (data->out_fd != 1)
		{
			printf("fermeture out_fd\n");
			printf("debut dup2\n");
			if (dup2(data->out_fd, 1) == -1)
			{
				perror("dup2 failed for out_fd");
				exit(EXIT_FAILURE);
			}
			printf("fin dup2\n");
			close(data->out_fd);
			printf("fin de la fermeture\n");
		}
		if (ft_check_function(data, args, path, arg) == -1)
		{
			printf("Command %s not found\n", arg->cmd);
			ft_free_child(args, data, arg);
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_algo_exec(t_struct *data, t_args *arg, int i, int cmd_count)
{
	char	**args;
	char	**true_path;

	if (!arg[i].cmd)
		return ;
	printf("debut ft_algo_exec\n");
	ft_check_i(i, cmd_count, data);
	true_path = ft_assign_path(data, arg[i].cmd);
	args = ft_fill_args(arg[i].cmd, arg[i].args);
	data->pid = fork();
	ft_pipe_exec(data, args, true_path, &arg[i]);
	if (i < cmd_count - 1)
		close(data->pipefd[1]);
	ft_2nd_exec(data, args, true_path);
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
	while (i < cmd_count)
	{
		if (!arg[i].cmd)
		{
			i++;
			continue ;
		}
		ft_algo_exec(data, arg, i, cmd_count);
		i++;
	}
	ft_exec_cleanup(data, arg, cmd_count);
}
