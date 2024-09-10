/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:01:37 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/10 17:45:48 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_check_function(t_list *parsing)
{
	if (parsing && parsing->content)
	{
		if (ft_strcmp(parsing->content[0], "ls") == 0)
			return (1);
		if (ft_strcmp(parsing->content[0], "cat") == 0)
			return (1);
		if (ft_strcmp(parsing->content[0], "echo") == 0)
			return (1);
		if (ft_strcmp(parsing->content[0], "cd") == 0)
			return (1);
		if (ft_strcmp(parsing->content[0], "pwd") == 0)
			return (1);
		if (ft_strcmp(parsing->content[0], "export") == 0)
			return (1);
		if (ft_strcmp(parsing->content[0], "unset") == 0)
			return (1);
		if (ft_strcmp(parsing->content[0], "env") == 0)
			return (1);
		if (ft_strcmp(parsing->content[0], "exit") == 0)
			return (1);
	}
	return (0);
}

char	**ft_get_path(void)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split(getenv("PATH"), ':');
	return (tab);
}

void	ft_hard_path(void)
{
	char	*path;

	path = getenv("PATH");
	if (!path)
	{
		printf("No path found\n");
		exit(1);
	}
}

void	ft_exec(t_list *parsing)
{
	char	**path;

	if (ft_check_function(parsing) == 0)
	{
		//printf("Command '%s' not found\n", parsing->content[0]);
		return ;
	}
	ft_hard_path();
	printf("hard path\n");
	path = ft_get_path();
	printf("path\n");
	if (parsing && parsing->content && parsing->next_content)
		ft_exec(parsing->next_content);
	if (parsing && parsing->content)
	{
		if (execve(parsing->content[0], parsing->content, path) == -1)
		{
			printf("Command '%s' not found\n", parsing->content[0]);
			return ;
		}
	}
}
