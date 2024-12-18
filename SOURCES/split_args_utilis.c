/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utilis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:33:51 by gprunet           #+#    #+#             */
/*   Updated: 2024/12/18 02:41:52 by gprunet          ###   ########.fr       */
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

int	check_input(t_struct *data, char *temp, t_args *args)
{
	if ((*args).input)
		return (0);
	if (ft_strchr(temp, '<') == 1 && data->redir[0] == 1)
		return (1);
	return (0);
}

int	check_output(t_struct *data, char *temp, t_args *args)
{
	if ((*args).output)
		return (0);
	if (ft_strchr(temp, '>') == 1 && data->redir[0] == 1)
		return (1);
	return (0);
}

int	check_true_redir(t_struct *data)
{
	int	i;

	i = 0;
	while (i <= data->nb_redir)
	{
		if (data->redir[i] == 1)
			return (1);
		i++;
	}
	return (0);
}

int	q_redir(t_struct *data, char *temp, t_args *args)
{
	int	i;
	int	count;

	if (data->nb_redir == 0 || check_true_redir(data) == 0)
		return (0);
	i = 0;
	count = 0;
	if (check_input(data, temp, args) == 1)
		return (1);
	if (check_output(data, temp, args) == 1)
		return (1);
	if ((*args).output || (*args).input)
	{
		while (temp[i])
		{
			if (temp[i] == '>' || temp[i] == '<')
				count++;
			if (count > 1 && data->redir[count] == 1)
				return (1);
			i++;
		}
	}
	return (0);
}

t_args	ft_assign_args(t_args *new_args, char **temp, t_struct *data)
{
	int (i) = 0;
	int (j) = 0;
	while (i < ft_tablen(temp))
	{
		if (q_redir(data, temp[i], new_args) == 1)
		{
			if (check_redirection(temp, new_args, &i, &j) == 1)
				continue ;
		}
		if (!(*new_args).cmd && check_built(temp[0], new_args, &i) == 1)
			continue ;
		if (ft_check_cmd(new_args, i, NULL) == 1)
			break ;
		if (check_string(temp[i], &i) == 1)
			continue ;
		if (verif_command(data, &temp[i], new_args) == 1)
			(*new_args).cmd = ft_strdup(temp[i]);
		else if ((*new_args).cmd)
			(*new_args).args[j++] = ft_strdup(temp[i]);
		else if (ft_check_cmd(new_args, i, "free") == 1)
			break ;
		i++;
	}
	post_assign_args(new_args, j, data);
	return (*new_args);
}
