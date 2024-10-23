/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:44:32 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/23 13:52:25 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_write_env(t_struct *data)
{
	int		i;
	int		j;

	i = open("/etc/environment", O_RDONLY);
	if (i == -1)
	{
		return (-1);
	}
	data->env = malloc (2 * 8);
	data->env[0] = malloc (120 * 8);
	j = read(i, data->env[0], 120);
	if (j == -1)
	{
		close(i);
		ft_free(data->env);
		return (-1);
	}
	data->env[0][j + 1] = '\0';
	data->env[1] = NULL;
	close (i);
	return (1);
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
