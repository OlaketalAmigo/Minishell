/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utilis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:33:51 by gprunet           #+#    #+#             */
/*   Updated: 2025/01/09 11:49:53 by gprunet          ###   ########.fr       */
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

int	c_args(char **temp)
{
	int	i;

	i = 0;
	while (temp[i])
		i++;
	return (i);
}

int	ft_check_hard_path(t_struct *data, char *arg)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split(arg, '/');
	while (tab[i])
	{
		if (ft_check_path(data, tab[i]) && !tab[i + 1])
		{
			ft_free(tab);
			return (1);
		}
		i++;
	}
	ft_free(tab);
	return (0);
}

void	post_assign_args(t_args *new_args, int j, t_struct *data)
{
	if ((*new_args).delimiter)
		data->heredoc = 1;
	if ((*new_args).args)
		(*new_args).args[j] = NULL;
}

t_args	ft_assign_args(t_args *args, char **temp, t_struct *data)
{
	int (i) = 0;
	int (j) = 0;
	while (i < ft_tablen(temp) && temp_check(temp, data, i) == 0)
	{
		if (q_redir(data, temp[i], args, i) == 1)
		{
			if (check_redirection(temp, args, &i, &j) == 1)
				continue ;
		}
		if (!(*args).cmd && check_built(temp[i], args, &i, ft_tablen(temp)))
			continue ;
		if (ft_check_cmd(args, i, NULL) == 1)
			break ;
		if (check_string(temp[i], &i) == 1)
			continue ;
		if (verif_command(data, &temp[i], args) == 1)
			(*args).cmd = ft_strdup(temp[i]);
		else if ((*args).cmd)
			(*args).args[j++] = ft_strdup(temp[i]);
		else if (ft_check_cmd(args, i, "free") == 1)
			break ;
		i++;
	}
	post_assign_args(args, j, data);
	return (*args);
}
