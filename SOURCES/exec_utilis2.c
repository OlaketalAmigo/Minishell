/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utilis2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:08:46 by gprunet           #+#    #+#             */
/*   Updated: 2024/09/19 12:58:49 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_child(char **args, t_struct *data)
{
	ft_free(data->flags);
	ft_free(data->cmds);
	ft_free(data->path);
	ft_free(args);
	ft_free(data->arg);
}

void	free_flags(char **flags)
{
	int	i;

	i = 0;
	while (flags[i])
	{
		if (i % 2 != 0 && i != 0)
		{
			free(flags[i]);
		}
		i++;
	}
	free(flags);
}

void	ft_fill_new_args(char **arg, char **new, char ***flags, char ***cmds)
{
	int	i;
	int	j;
	int	k;
	int	args;

	j = 0;
	k = 0;
	args = 0;
	while (arg[args])
	{
		i = 0;
		new = ft_split_cleared(arg[args], ' ');
		while (new[i])
		{
			if (ft_strchr(new[i], '|') == 1)
				break ;
			if (is_flag(new[i]))
				(*flags)[j++] = ft_strdup(new[i]);
			else if (is_empty(new[i]) == 0)
				(*cmds)[k++] = ft_strdup(new[i]);
			i++;
		}
		args++;
		ft_free(new);
	}
}

char	**check_access(char *tmp, int s)
{
	char	**tab;

	if (s == 1)
	{
		tab = ft_split(tmp, ' ');
		if (access(tab[0], X_OK) == 0)
		{
			free(tmp);
			return (tab);
		}
		return (NULL);
	}
	else
	{
		tab = malloc(sizeof(char *) * 2);
		tab[0] = ft_strdup(tmp);
		tab[1] = NULL;
		free(tmp);
		return (tab);
	}
	return (NULL);
}

int	ft_hard_path(char *arg)
{
	if (access(arg, X_OK) == 0)
		return (1);
	return (0);
}
