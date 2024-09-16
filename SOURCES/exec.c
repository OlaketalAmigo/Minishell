/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:01:37 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/16 11:36:04 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_flag(char *arg)
{
	if (arg)
	{
		if (arg[0] == '-' && arg[1] != '\0' && arg[1] != ' ')
			return (1);
	}
	return (0);
}

int	is_empty(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	while (arg[i] == ' ')
		i++;
	if (arg[i] && arg[i] != ' ')
		return (0);
	return (1);
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

void	split_args(char **arg, char ***flags, char ***cmds)
{
	int		i;
	int		j;
	int		k;
	char	**new_args;

	i = 0;
	j = 0;
	k = 0;
	new_args = ft_split(arg[0], ' ');
	i = 0;
	while (new_args[i])
	{
		if (is_flag(new_args[i]))
			j++;
		else if (is_empty(new_args[i]) == 0)
			k++;
		i++;
	}
	*flags = malloc(sizeof(char *) * (j + 1));
	*cmds = malloc(sizeof(char *) * (k + 1));
	(*flags)[j] = NULL;
	(*cmds)[k] = NULL;
	i = 0;
	j = 0;
	k = 0;
	while (new_args[i])
	{
		if (is_flag(new_args[i]))
		{
			(*flags)[j] = new_args[i];
			j++;
		}
		else if (is_empty(new_args[i]) == 0)
		{
			(*cmds)[k] = new_args[i];
			k++;
		}
		i++;
	}
	free_flags(new_args);
}

char	**ft_true_path(t_struct *data, char **arg)
{
	char	**tab;
	char	*tmp;
	int		i;

	i = 0;
	while (data->path[i])
	{
		tmp = ft_strjoin(data->path[i], arg[0]);
		if (ft_strchr(tmp, ' ') == 1)
		{
			tab = ft_split(tmp, ' ');
			if (access(tab[0], X_OK) == 0)
			{
				free(tmp);
				return (tab);
			}
		}
		if (access(tmp, X_OK) == 0)
		{
			tab = malloc(sizeof(char *) * 2);
			tab[0] = ft_strdup(tmp);
			tab[1] = NULL;
			free(tmp);
			return (tab);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

int	ft_hard_path(char **arg)
{
	if (access(arg[0], X_OK) == 0)
		return (1);
	return (0);
}

void	ft_exec(t_struct *data)
{
	char	**true_path;
	char	**args;
	int		i;
	int		j;
	pid_t	pid;

	i = 0;
	j = 0;
	data->path = ft_split(getenv("PATH"), ':');
	split_args(data->arg, &data->flags, &data->cmds);
	if (!ft_hard_path(data->cmds))
		true_path = ft_true_path(data, data->cmds);
	else
	{
		true_path = malloc(sizeof(char *) * 2);
		true_path[0] = ft_strdup(data->cmds[0]);
		true_path[1] = NULL;
	}
	while (data->cmds[i] && is_empty(data->cmds[i]) == 0)
		i++;
	while (data->flags[j] && is_empty(data->flags[j]) == 0)
		j++;
	i = i + j;
	args = malloc(sizeof(char *) * (i + 1));
	i = 0;
	j = 0;
	while (data->cmds[j] && is_empty(data->cmds[j]) == 0)
		args[i++] = ft_strdup(data->cmds[j++]);
	j = 0;
	while (data->flags[j])
		args[i++] = ft_strdup(data->flags[j++]);
	args[i] = NULL;
	pid = fork();
	if (pid == 0)
	{
		if (args && true_path)
		{
			if (execve(true_path[0], args, data->env) == -1)
			{
				printf("Command %s not found\n", data->cmds[0]);
				ft_free(data->flags);
				ft_free(data->cmds);
				ft_free(data->path);
				ft_free(args);
				ft_free(data->arg);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			printf("Command %s not found\n", data->cmds[0]);
			ft_free(data->flags);
			ft_free(data->cmds);
			ft_free(data->path);
			ft_free(args);
			ft_free(data->arg);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		ft_free(true_path);
		ft_free(args);
	}
}
