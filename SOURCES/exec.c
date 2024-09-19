/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:01:37 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/19 15:56:48 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_args(char **arg, char ***flags, char ***cmds)
{
	int		i;
	int		j;
	int		k;
	int		args;
	char	**new_args;

	i = 0;
	j = 0;
	k = 0;
	args = 0;
	while (arg[args])
	{
		new_args = ft_split_cleared(arg[args], ' ');
		i = 0;
		if (ft_strchr(arg[args], '|') == 1)
		{
			ft_free(new_args);
			args++;
			continue ;
		}
		while (new_args[i])
		{
			if (is_flag(new_args[i]) == 1)
				j++;
			else if (is_empty(new_args[i]) == 0)
				k++;
			i++;
		}
		args++;
		ft_free(new_args);
	}
	*flags = malloc(sizeof(char *) * (j + 1));
	*cmds = malloc(sizeof(char *) * (k + 1));
	(*flags)[j] = NULL;
	(*cmds)[k] = NULL;
	ft_fill_new_args(arg, new_args, flags, cmds);
}

char	**ft_true_path(t_struct *data, char *arg)
{
	char	**tab;
	char	*tmp;
	int		i;

	i = 0;
	while (data->path[i])
	{
		tmp = ft_strjoin(data->path[i], arg);
		if (ft_strchr(tmp, ' ') == 1)
		{
			tab = check_access(tmp, 1);
			if (tab)
				return (tab);
		}
		else if (access(tmp, X_OK) == 0)
		{
			tab = check_access(tmp, 0);
			if (tab)
				return (tab);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

char	**ft_fill_args(char **cmds, char **flags)
{
	int		i;
	int		j;
	int		k;
	char	**args;

	i = 0;
	j = 0;
	k = 0;
	while (cmds[i] && is_empty(cmds[i]) == 0)
		i++;
	while (flags[j] && is_empty(flags[j]) == 0)
		j++;
	args = malloc(sizeof(char *) * (i + j + 1));
	i = 0;
	j = 0;
	if (cmds[j])
	{
		args[i++] = ft_strdup(cmds[j++]);
		if (flags[k])
			args[i++] = ft_strdup(flags[k++]);
	}
	args[i] = NULL;
	return (args);
}

void	ft_pipe_exec(t_struct *data, char **args, char **true_path)
{
	if (data->pid == 0)
	{
		if (data->in_fd != 0)
		{
			dup2(data->in_fd, 0);
			close(data->in_fd);
		}
		if (data->out_fd != 1)
		{
			dup2(data->out_fd, 1);
			close(data->out_fd);
		}
		if (!true_path)
		{
			printf("Command %s not found\n", data->cmds[0]);
			ft_free_child(args, data);
			exit(EXIT_FAILURE);
		}
		if (ft_check_function(data, args, true_path) == -1)
		{
			printf("Command %s not found\n", data->cmds[0]);
			ft_free_child(args, data);
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_exec(t_struct *data)
{
	char	**true_path;
	char	**args;
	int		cmd_count;
	int		i;

	i = 0;
	cmd_count = 0;
	data->in_fd = 0;
	data->path = ft_split(getenv("PATH"), ':');
	split_args(data->arg, &data->flags, &data->cmds);
	//while (data->cmds[cmd_count])
	cmd_count = 1;
	while (i < cmd_count)
	{
		if (i < cmd_count - 1)
		{
			if (pipe(data->pipefd) == -1)
				exit(EXIT_FAILURE);
			data->out_fd = data->pipefd[1];
		}
		else
			data->out_fd = STDOUT_FILENO;
		if (!ft_hard_path(data->cmds[i]))
			true_path = ft_true_path(data, data->cmds[i]);
		else
		{
			true_path = malloc(sizeof(char *) * 2);
			true_path[0] = ft_strdup(data->cmds[i]);
			true_path[1] = NULL;
		}
		args = ft_fill_args(data->cmds, data->flags);
		data->pid = fork();
		ft_pipe_exec(data, args, true_path);
		if (i < cmd_count - 1)
			close(data->pipefd[1]);
		if (data->in_fd != 0)
			close(data->in_fd);
		data->in_fd = data->pipefd[0];
		if (true_path)
			ft_free(true_path);
		ft_free(args);
		if (data->pid != 0)
			waitpid(data->pid, NULL, 0);
		i++;
	}
}
