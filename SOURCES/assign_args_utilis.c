/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_args_utilis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehe <hehe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:25:18 by gprunet           #+#    #+#             */
/*   Updated: 2024/12/20 00:21:22 by hehe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	ft_check_cmd(t_args *new_args, int i, char *str)
{
	if (i > 0 && (*new_args).cmd == NULL && str == NULL)
	{
		free((*new_args).args);
		(*new_args).args = NULL;
		return (1);
	}
	if ((*new_args).cmd == NULL && str)
	{
		free((*new_args).args);
		(*new_args).args = NULL;
		return (1);
	}
	return (0);
}

int	check_built(char *temp, t_args *new_args, int *i, char **t)
{
	if ((*new_args).input && !(*new_args).cmd && *i + 1 < ft_tablen(t))
	{
		(*new_args).cmd = ft_strdup(t[*i + 1]);
		*i = *i + 2;
		return (1);
	}
	if (ft_check_builtins_init(temp) == 1 && (*new_args).cmd == NULL)
	{
		(*new_args).cmd = ft_strdup(temp);
		*i = *i + 1;
		return (1);
	}
	else if ((*new_args).cmd == NULL && ft_strchr(temp, '|') == 0)
	{
		(*new_args).cmd = ft_strdup(temp);
		*i = *i + 1;
		return (1);
	}
	return (0);
}

int	check_string(char *temp, int *i)
{
	if (!temp)
		return (0);
	if (ft_strchr(temp, '|') == 1 && ft_strlen(temp) > 1)
		return (0);
	if ((ft_strchr(temp, '|') == 1 && *i == 0) || is_empty(temp) == 1)
	{
		*i = *i + 1;
		return (1);
	}
	return (0);
}

int	verif_command(t_struct *data, char **cmd, t_args *new_args)
{
	char	**tab;

	tab = NULL;
	if (new_args->cmd != NULL)
		return (0);
	if (ft_strchr(*cmd, '/') == 1)
	{
		if (ft_check_hard_path(data, *cmd))
		{
			tab = ft_split(*cmd, '/');
			free(*cmd);
			*cmd = ft_strdup(tab[ft_tablen(tab) - 1]);
			ft_free(tab);
			return (1);
		}
	}
	if (ft_check_builtins_init(*cmd) == 1 || ft_strchr(*cmd, '|') == 1)
		return (1);
	else if (ft_check_path(data, *cmd))
		return (1);
	return (0);
}
