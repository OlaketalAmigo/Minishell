/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:05:50 by gprunet           #+#    #+#             */
/*   Updated: 2024/10/29 16:26:05 by gprunet          ###   ########.fr       */
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

void	ft_exec_init(t_struct *data, t_args **arg, int *cmd_count)
{
	data->count = 0;
	data->path = ft_split(getenv("PATH"), ':');
	data->in_fd = 0;
	data->out_fd = 1;
	data->pid = 0;
	data->heredoc = 0;
	data->saved_stdin = -1;
	data->saved_stdout = -1;
	*cmd_count = split_args(data->arg, arg, data);
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

int	pipe_check(t_struct *data, int i, int cmd_count)
{
	if (i < cmd_count - 1)
	{
		if (pipe(data->pipefd) == -1)
		{
			perror("pipe error");
			return (-1);
		}
		data->out_fd = data->pipefd[1];
	}
	else
		data->out_fd = STDOUT_FILENO;
	return (0);
}

void	reset_pipe_exit(t_struct *data, int i, int cmd_count)
{
	if (i < cmd_count - 1)
	{
		close(data->pipefd[1]);
		data->in_fd = data->pipefd[0];
	}
}
