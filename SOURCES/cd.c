/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:08:47 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/07 12:29:59 by gprunet          ###   ########.fr       */
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
		// PRINTF MALLOC FAILED
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
			printf("HOME not set\n");
		if (path)
			free(path);
		return (1);
	}
	else if (i == 2)
	{
		path = args[1];
		chdir(path);
		return (1);
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

	printf("started builtin cd\n");
	i = ft_nb_arg(args);
	cd = NULL;
	ft_cd_main(data, args, i, cd);
	return (0);
}

int	ft_cd_pipe(t_struct *data, t_args *arg, char **args, char **path)
{
	int		i;
	char	*cd;

	printf("started builtin cd\n");
	i = ft_nb_arg(args);
	cd = NULL;
	ft_cd_main(data, args, i, cd);
	ft_free_child(args, data, arg, path);
	exit(EXIT_SUCCESS);
}