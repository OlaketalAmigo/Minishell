/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:05:50 by gprunet           #+#    #+#             */
/*   Updated: 2024/10/07 12:31:39 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_init(t_struct *data, t_args **arg, int *cmd_count)
{
	data->path = ft_split(getenv("PATH"), ':');
	data->in_fd = 0;
	data->out_fd = 1;
	data->pid = 0;
	*cmd_count = split_args(data->arg, arg, data);
}

void	ft_check_i(int i, int cmd_count, t_struct *data)
{
	if (i < cmd_count - 1)
	{
		if (pipe(data->pipefd) == -1)
		{
			close(data->pipefd[0]);
			exit(EXIT_FAILURE);
		}
		data->out_fd = data->pipefd[1];
	}
	else
		data->out_fd = STDOUT_FILENO;
}

void	ft_2nd_exec(t_struct *data, char **args, char **true_path)
{
	if (data->in_fd != 0)
		close(data->in_fd);
	data->in_fd = data->pipefd[0];
	if (true_path)
		ft_free(true_path);
	ft_free(args);
	if (data->pid != 0)
		waitpid(data->pid, NULL, 0);
}

char	**ft_assign_path(t_struct *data, char *cmd)
{
	char	**true_path;

	if (!ft_hard_path(cmd))
		true_path = ft_true_path(data, cmd);
	else
	{
		true_path = malloc(sizeof(char *) * 2);
		true_path[0] = ft_strdup(cmd);
		true_path[1] = NULL;
	}
	return (true_path);
}
