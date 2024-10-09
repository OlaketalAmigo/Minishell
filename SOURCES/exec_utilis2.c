/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utilis2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:08:46 by gprunet           #+#    #+#             */
/*   Updated: 2024/10/07 12:30:47 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_builtins(char *arg)
{
	if (ft_strncmp(arg, "<<", 2) == 1)
		return (1);
	if (ft_strncmp(arg, "echo", 4) == 1)
		return (1);
	if (ft_strncmp(arg, "cd", 2) == 1)
		return (1);
	if (ft_strncmp(arg, "pwd", 3) == 1)
		return (1);
	if (ft_strncmp(arg, "export", 6) == 1)
		return (1);
	if (ft_strncmp(arg, "unset", 5) == 1)
		return (1);
	if (ft_strncmp(arg, "env", 3) == 1)
		return (1);
	if (ft_strncmp(arg, "exit", 4) == 1)
		return (1);
	return (0);
}

void	ft_free_child(char **args, t_struct *data, t_args *arg, char **path)
{
	free(arg->cmd);
	ft_free(arg->args);
	free(arg->input);
	free(arg->output);
	ft_free(data->path);
	if (path)
		ft_free(path);
	ft_free(args);
	ft_free(data->arg);
	free(arg);
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

char	**ft_true_path(t_struct *data, char *cmd)
{
	char	**tab;
	char	*tmp;
	int		i;

	i = 0;
	tab = NULL;
	while (data->path[i] || cmd)
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
