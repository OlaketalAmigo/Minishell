/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utilis3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:36:49 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/02 13:50:03 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_cleared(char *s, char c)
{
	char	**word_list;
	int		length;

	length = ft_strlen(s);
	word_list = malloc (sizeof(char *) * (ft_countword(s, c) + 1));
	if (!word_list)
		return (NULL);
	word_list = ft_mecanism(length, word_list, s, c);
	word_list = ft_clear_to_function(word_list);
	return (word_list);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] == s2[i] && s1[i] && s2[i])
			i++;
		else
		{
			return (-1);
		}
	}
	return (1);
}

int	ft_execve(char **path, char **args, t_struct *data, t_args *arg)
{
	if (!path || !path[0])
	{
		printf("Command %s not found\n", arg->cmd);
		ft_free_child(args, data, arg);
		exit(EXIT_FAILURE);
	}
	return (execve(path[0], args, data->env));
}

int	ft_check_function(t_struct *d, char **args, char **path, t_args *arg)
{
	if (!args)
		return (-1);
	if (ft_strncmp(args[0], "echo", 4) == 1)
		return (ft_echo(args, 1));
	else if (ft_strncmp(args[0], "export", 6) == 1)
		return (ft_export(d, args, 1));
	else if (ft_strncmp(args[0], "unset", 5) == 1)
		return (-1);
	else if (ft_strncmp(args[0], "pwd", 3) == 1)
		return (ft_pwd(args, 1));
	else if (ft_strncmp(args[0], "cd", 2) == 1)
		return (ft_cd(d, args, 1));
	else if (ft_strncmp(args[0], "env", 3) == 1)
		return (-1);
	else if (ft_strncmp(args[0], "exit", 4) == 1)
		return (ft_exit(args, 1));
	else
		return (ft_execve(path, args, d, arg));
}

char	**ft_true_path(t_struct *data, char *cmd)
{
	char	**tab;
	char	*tmp;
	int		i;

	i = 0;
	tab = NULL;
	while (data->path[i] || cmd)
	{
		tmp = ft_strjoin(data->path[i], cmd);
		if (ft_strchr(tmp, ' ') == 1)
			tab = check_access(tmp, 1);
		else if (access(tmp, X_OK) == 0)
			tab = check_access(tmp, 0);
		free(tmp);
		if (tab)
			break ;
		i++;
	}
	return (tab);
}
