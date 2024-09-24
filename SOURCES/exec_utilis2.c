/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utilis2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehe <hehe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:08:46 by gprunet           #+#    #+#             */
/*   Updated: 2024/09/23 17:16:03 by hehe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_child(char **args, t_struct *data, t_args *arg)
{
	free(arg->cmd);
	ft_free(arg->args);
	free(arg);
	ft_free(data->path);
	ft_free(args);
	ft_free(data->arg);
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
