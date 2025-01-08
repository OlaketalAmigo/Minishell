/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:40:51 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/08 19:45:09 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] && s2[i] && s1[i] == s2[i])
			i++;
		else
			return (-1);
	}
	return (1);
}

void	ft_free_child2(char **args, t_struct *data, char **path)
{
	ft_free(data->path);
	ft_free(path);
	ft_free(args);
	ft_free(data->arg);
	ft_free(data->env);
	if (data->path_to_home)
		free(data->path_to_home);
	free(data->redir);
}

void	heredoc_exit(t_struct *data)
{
	if (data->heredoc == 2)
	{
		close(data->pipefd[0]);
		close(data->saved_stdin);
	}
}

void	ft_set_up_data_path(t_struct *data)
{
	char	*pog;
	char	*pag;
	int		i;

	i = -1;
	pog = malloc(5);
	if (!pog)
	{
		data->path = NULL;
		return ;
	}
	pog[0] = 80;
	pog[1] = 65;
	pog[2] = 84;
	pog[3] = 72;
	pog[4] = '\0';
	pag = ft_get_from_env(data, pog);
	data->path = ft_split(pag, ':');
	if (pag)
		free(pag);
}
