/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:01:37 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/18 14:43:53 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_args(char **arg, char ***flags, char ***cmds)
{
	int		i;
	int		j;
	int		k;
	char	**new_args;

	i = 0;
	j = 0;
	k = 0;
	new_args = ft_split_cleared(arg[0], ' ');
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
	ft_fill_new_args(new_args, flags, cmds);
	printf("%s\n", (*cmds)[0]);
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
			tab = check_access(tmp, 1);
			if (tab)
				return (tab);
		}
		else if (access(tmp, X_OK) == 0)
		{
			tab = check_access(tmp, 0);
			if (tab)
				return (tab);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

char	**ft_fill_args(char **cmds, char **flags)
{
	int		i;
	int		j;
	char	**args;

	i = 0;
	j = 0;
	while (cmds[i] && is_empty(cmds[i]) == 0)
		i++;
	while (flags[j] && is_empty(flags[j]) == 0)
		j++;
	i = i + j;
	args = malloc(sizeof(char *) * (i + 1));
	i = 0;
	j = 0;
	while (cmds[j] && is_empty(cmds[j]) == 0)
		args[i++] = ft_strdup(cmds[j++]);
	j = 0;
	while (flags[j])
		args[i++] = ft_strdup(flags[j++]);
	args[i] = NULL;
	return (args);
}

void	ft_pipe_exec(t_struct *data, char **args, char **true_path, pid_t pid)
{
	if (pid == 0)
	{
		if (args && true_path)
		{
			if (execve(true_path[0], args, data->env) == -1)
			{
				printf("Command %s not found\n", data->cmds[0]);
				ft_free_child(args, data);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			printf("Command %s not found\n", data->cmds[0]);
			ft_free_child(args, data);
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

void	ft_exec(t_struct *data)
{
	char	**true_path;
	char	**args;
	pid_t	pid;

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
	args = ft_fill_args(data->cmds, data->flags);
	pid = fork();
	ft_pipe_exec(data, args, true_path, pid);
}
