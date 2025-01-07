/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:44:32 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/06 11:34:58 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_write_starting_env(char **tab)
{
	char	**new;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (tab)
	{
		new = malloc (2 * 8);
		new[0] = malloc (ft_strlen(tab[0]) + 1);
		if (!new)
			return (NULL);
		while (++i < ft_strlen(tab[0]))
		{
			if (tab[0][i] == 34 || tab[0][i] == 10)
				continue ;
			else
				new[0][++j] = tab[0][i];
		}
		new[0][j] = '\0';
		new[1] = NULL;
		return (new);
	}
	return (NULL);
}

void	ft_write_env(t_struct *data)
{
	int		i;
	int		j;
	char	**tab;

	i = open("/etc/environment", O_RDONLY);
	if (i == -1)
		return ;
	tab = malloc (2 * 8);
	tab[0] = malloc (120 * 8);
	j = read(i, tab[0], 120);
	if (j == -1)
	{
		close(i);
		return (ft_free(tab));
	}
	tab[0][j + 1] = '\0';
	tab[1] = NULL;
	data->env = ft_write_starting_env(tab);
	i = -1;
	close (i);
}

void	ft_set_up_env(t_struct *data, char **environ)
{
	int		i;
	int		j;
	char	**tab;
	char	*x;

	if (environ[0] == NULL)
		ft_write_env(data);
	else
	{
		data->env = environ;
		i = -1;
		tab = malloc ((ft_nb_arg(data->env) + 1) * 8);
		while (++i < ft_nb_arg(data->env))
		{
			j = -1;
			tab[i] = malloc (ft_strlen(data->env[i]) + 1);
			while (++j < ft_strlen(data->env[i]))
				tab[i][j] = data->env[i][j];
			tab[i][j] = '\0';
		}
		tab[i] = NULL;
		data->env = tab;
	}
	x = "?=0";
	ft_export_add(data, x);
}
