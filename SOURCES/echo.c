/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:27:45 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/23 15:48:59 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_good_flag(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 1;
	if (s[0] == 45)
	{
		while (s[i])
		{
			if (s[i] != 'n')
				return (-1);
			else
				i++;
		}
	}
	else
		return (-1);
	return (1);
}

int	ft_is_wrong_flag(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 1;
	if (s[0] == 45)
	{
		while (s[i])
		{
			if (s[i] != 'n')
				return (1);
			else
				i++;
		}
	}
	return (-1);
}

int	ft_count_good_flags(char **tab)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (tab[i])
	{
		if (ft_is_good_flag(tab[i]) == 1)
			j++;
		if (ft_is_wrong_flag(tab[i]) == 1)
			return (-1);
		i++;
	}
	return (j);
}

int	ft_echo(t_struct *data, char **args)
{
	char	*update;
	int		option;
	int		i;

	option = 0;
	i = 1;
	if (ft_count_good_flags(args) >= 1)
		option = 1;
	if (ft_count_good_flags(args) == -1)
		return (-1);
	while (args[i])
	{
		if (ft_strncmp("-", args[i], 1) == 1)
			i++;
		else
			break ;
	}
	while (args[i])
		printf("%s ", args[i++]);
	if (option == 0)
		printf("\n");
	update = "?=0";
	ft_export_update(data, update);
	return (0);
}

int	ft_echo_pipe(t_struct *data, t_args *arg, char **args, char **path)
{
	char	*update;
	int		option;
	int		i;

	option = 0;
	i = 1;
	if (ft_count_good_flags(args) >= 1)
		option = 1;
	if (ft_count_good_flags(args) == -1)
		return (-1);
	while (args[i])
	{
		if (ft_strncmp("-", args[i], 1) == 1)
			i++;
		else
			break ;
	}
	while (args[i])
		printf("%s ", args[i++]);
	if (option == 0)
		printf("\n");
	update = "?=0";
	ft_export_update(data, update);
	ft_free_child(args, data, arg, path);
	exit(EXIT_SUCCESS);
}
