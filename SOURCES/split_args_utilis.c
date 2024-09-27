/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utilis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:33:51 by gprunet           #+#    #+#             */
/*   Updated: 2024/09/27 13:25:34 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_path(t_struct *data, char *arg)
{
	char	**tab;
	char	*tmp;
	int		i;

	i = 0;
	tab = NULL;
	while (data->path[i] && arg)
	{
		tmp = ft_strjoin(data->path[i], arg);
		if (ft_strchr(tmp, ' ') == 1)
			tab = check_access(tmp, 1);
		else if (access(tmp, X_OK) == 0)
			tab = check_access(tmp, 0);
		free(tmp);
		if (tab)
			break ;
		i++;
	}
	if (tab)
	{
		ft_free(tab);
		return (1);
	}
	return (0);
}

int	c_args(char **temp, t_struct *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (temp[i])
	{
		if (ft_strchr(temp[i], '|') == 0)
		{
			if (!ft_check_path(data, temp[i]))
				count++;
		}
		i++;
	}
	return (count);
}

int	count_commands(char **arg, t_struct *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (is_empty(arg[i]) == 0)
		{
			if (ft_check_builtins(arg[i]) == 1 || ft_strchr(arg[i], '|') == 1)
				count++;
			else if (ft_check_path(data, arg[i]))
				count++;
		}
		i++;
	}
	return (count);
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

t_args	ft_assign_args(t_args *new_args, char **temp, t_struct *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (temp[i])
	{
		if (check_built(temp[i], new_args, &i) == 1)
			continue ;
		if (ft_check_cmd(new_args, i, NULL) == 1)
			break ;
		if (check_string(temp[i], &i) == 1)
			continue ;
		if (ft_check_path(data, temp[i]) && (*new_args).cmd == NULL)
			(*new_args).cmd = ft_strdup(temp[i]);
		else if ((*new_args).cmd)
			(*new_args).args[j++] = ft_strdup(temp[i]);
		else if (ft_check_cmd(new_args, i, "free") == 1)
			break ;
		i++;
	}
	if ((*new_args).args)
		(*new_args).args[j] = NULL;
	return (*new_args);
}
