/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utilis2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehe <hehe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:08:46 by gprunet           #+#    #+#             */
/*   Updated: 2025/01/07 21:47:51 by hehe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_child(char **args, t_struct *data, t_args **arg, char **path)
{
	if (data->total > 1)
	{
		if (data->n_in == 0 && data->n_out == 0)
		{
			close(data->pipefd[0]);
			close(data->pipefd[1]);
		}
	}
	if (data->input)
		close(data->saved_stdin);
	if (data->output)
		close(data->saved_stdout);
	ft_free(data->path);
	ft_free(path);
	ft_free(args);
	ft_free(data->arg);
	ft_free(data->env);
	if (data->path_to_home)
		free(data->path_to_home);
	free(data->redir);
	ft_free_struct(arg, data->total);
}

char	**check_access(char *tmp, int s)
{
	char	**tab;

	if (s == 1)
	{
		tab = ft_split(tmp, ' ');
		if (access(tab[0], X_OK) == 0)
			return (tab);
		ft_free(tab);
	}
	else
	{
		tab = malloc(sizeof(char *) * 2);
		tab[0] = ft_strdup(tmp);
		tab[1] = NULL;
		return (tab);
	}
	return (NULL);
}

int	ft_hard_path(char *arg)
{
	if (!arg)
		return (0);
	if (access(arg, X_OK) == 0)
		return (1);
	return (0);
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

char	**ft_true_path(t_struct *data, char *cmd)
{
	char	**tab;
	char	*tmp;
	int		i;

	i = 0;
	tab = NULL;
	while (data->path[i] && cmd)
	{
		tmp = ft_strjoin(data->path[i], cmd);
		if (ft_strchr(tmp, ' ') == 1)
			tab = check_access(tmp, 1);
		else if (access(tmp, X_OK) == 0)
			tab = check_access(tmp, 0);
		free(tmp);
		if (tab)
			break ;
		i++;
	}
	return (tab);
}
