/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:01:37 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/12 15:08:08 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '/';
	i++;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_strdup(char *s)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_true_path(t_struct *data, t_list *parsing)
{
	char	**tab;
	int		i;

	i = 0;
	tab = NULL;
	while (data->path[i])
	{
		data->path[i] = ft_strjoin(data->path[i], parsing->content[0]);
		if (access(data->path[i], X_OK) == 0)
		{
			printf("path = %s\n", data->path[i]);
			tab = ft_split(data->path[i], ' ');
			return (tab);
		}
		i++;
	}
	return (tab);
}

int	ft_hard_path(t_list *parsing)
{
	if (access(parsing->content[0], X_OK) == 0)
		return (1);
	return (0);
}

void	ft_exec(t_list *parsing, t_struct *data)
{
	char	**true_path;
	pid_t	pid;

	data->path = ft_split(getenv("PATH"), ':');
	if (!ft_hard_path(parsing))
		true_path = ft_true_path(data, parsing);
	else
		true_path = ft_split(parsing->content[0], ' ');
	pid = fork();
	if (pid == 0)
	{
		if (parsing && parsing->content)
		{
			if (execve(true_path[0], true_path, data->env) == -1)
			{
				printf("Command %s not found\n", parsing->content[0]);
				ft_free(true_path);
				return ;
			}
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		ft_free(true_path);
	}
}
