/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utilis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:33:51 by gprunet           #+#    #+#             */
/*   Updated: 2024/10/07 12:40:34 by gprunet          ###   ########.fr       */
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
		if (ft_strchr(temp[i], '|') == 0 && is_empty(temp[i]) == 0)
		{
			if ((i > 1 && ft_check_path(data, temp[i - 2])))
				count++;
			else if (!ft_check_path(data, temp[i]))
				count++;
		}
		i++;
	}
	return (count);
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

int	count_commands(char **arg, t_struct *data)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		//printf("arg[%d] = %s\n", i, arg[i]);
		if (check_redirection_cmd(arg[i]) == 1)
		{
			count++;
			i++;
			continue ;
		}
		if (ft_strchr(arg[i], '/') == 1)
		{
			if (ft_check_hard_path(data, arg[i]))
				count++;
		}
		else if (is_empty(arg[i]) == 0)
		{
			if (ft_check_builtins_init(arg[i]) == 1 || ft_strchr(arg[i], '|') == 1)
				count++;
			else if (ft_check_path(data, arg[i]))
				count++;
		}
		i++;
	}
	return (count);
}

t_args	ft_assign_args(t_args *new_args, char **temp, t_struct *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (temp[i])
	{
		if (check_heredoc(temp, new_args, &i) == 1)
			continue ;
		if (check_redirection(temp, new_args, &i, &j) == 1)
			continue ;
		if (!(*new_args).cmd && check_built(temp[0], new_args, &i) == 1)
			continue ;
		if (ft_check_cmd(new_args, i, NULL) == 1)
			break ;
		if (check_string(temp[i], &i) == 1)
			continue ;
		if (verif_command(data, &temp[i], new_args) == 1)
			(*new_args).cmd = ft_strdup(temp[i]);
		else if ((*new_args).cmd && check_redirection(temp, new_args, &i, &j) == 0 && temp[i])
			(*new_args).args[j++] = ft_strdup(temp[i]);
		else if (ft_check_cmd(new_args, i, "free") == 1)
			break ;
		i++;
	}
	if ((*new_args).args)
		(*new_args).args[j] = NULL;
	return (*new_args);
}
