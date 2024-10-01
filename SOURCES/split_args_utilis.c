/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utilis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehe <hehe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:33:51 by gprunet           #+#    #+#             */
/*   Updated: 2024/10/01 23:04:40 by hehe             ###   ########.fr       */
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
		if (ft_strchr(arg[i], '/') == 1)
		{
			if (ft_check_hard_path(data, arg[i]))
				count++;
		}
		else if (is_empty(arg[i]) == 0)
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
	if (ft_check_builtins(*cmd) == 1 || ft_strchr(*cmd, '|') == 1)
		return (1);
	else if (ft_check_path(data, *cmd))
		return (1);
	return (0);
}

int	check_redirection(char **temp, t_args *new_args, int *i)
{
	if (ft_strncmp(temp[*i], "<", 1) == 0 && temp[*i + 2])
	{
		(*new_args).input = ft_strdup(temp[*i + 2]);
		*i = *i + 3;
		return (1);
	}
	if (ft_strncmp(temp[*i], ">", 1) == 0 && temp[*i + 2])
	{
		(*new_args).output = ft_strdup(temp[*i + 2]);
		(*new_args).append = 0;
		*i = *i + 3;
		return (1);
	}
	if (ft_strncmp(temp[*i], ">>", 2) == 0 && temp[*i + 2])
	{
		(*new_args).output = ft_strdup(temp[*i + 2]);
		(*new_args).append = 1;
		*i = *i + 3;
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
		printf("temp[%d] = %s\n", i, temp[i]);
		if (check_redirection(temp, new_args, &i) == 1)
			continue ;
		if (check_built(temp[i], new_args, &i) == 1)
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
	if ((*new_args).args)
		(*new_args).args[j] = NULL;
	return (*new_args);
}
