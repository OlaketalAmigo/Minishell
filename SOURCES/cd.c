/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:08:47 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/23 15:48:49 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_home(char *s1)
{
	int		i;
	int		j;
	char	*s2;

	i = 0;
	j = 4;
	s2 = malloc (((ft_strlen(s1) - 5) + 1) * 1);
	if (!s2)
	{
		return (NULL);
	}
	while (s1[++j])
	{
		s2[i] = s1[j];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_get_home(t_struct *data)
{
	char	*tmp;
	int		i;

	i = -1;
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], "HOME=", 5) == 1)
		{
			tmp = ft_remove_home(data->env[i]);
			return (tmp);
		}
	}
	return (NULL);
}

int	ft_cd_main(t_struct *data, char **args, int i, char *path)
{
	if (i == 1)
	{
		path = ft_get_home(data);
		if (path)
			chdir(path);
		else
			return (printf("HOME not set\n"), -1);
		return (free(path), 1);
	}
	else if (i == 2)
	{
		path = args[1];
		if (chdir(path) == 0)
			return (1);
		printf("cd: %s: No such file or directory\n", args[1]);
		return (-1);
	}
	else
	{
		printf("cd: string not in pwd: %s\n", args[1]);
		return (-1);
	}
}

int	ft_cd(t_struct *data, char **args)
{
	int		i;
	char	*cd;
	char	*update;

	i = ft_nb_arg(args);
	cd = NULL;
	if (ft_cd_main(data, args, i, cd) == 1)
		update = "?=0";
	else
		update = "?=1";
	ft_export_update(data, update);
	return (0);
}

int	ft_cd_pipe(t_struct *data, t_args *arg, char **args, char **path)
{
	int		i;
	char	*cd;
	char	*update;

	i = ft_nb_arg(args);
	cd = NULL;
	if (ft_cd_main(data, args, i, cd) == 1)
		update = "?=0";
	else
		update = "?=1";
	ft_export_update(data, update);
	ft_free_child(args, data, arg, path);
	exit(EXIT_SUCCESS);
}
