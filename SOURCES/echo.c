/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:27:45 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/19 16:38:55 by tfauve-p         ###   ########.fr       */
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

int	ft_count_wrong_flags(char **tab)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (tab[i])
	{
		if (ft_is_wrong_flag(tab[i]) == 1)
		{
			printf("mauvais flag = %s\n", tab[i]);
			j++;
		}
		i++;
	}
	return (j);
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
		{
			printf("bon flag = %s\n", tab[i]);
			j++;
		}
		i++;
	}
	return (j);
}

int	ft_echo(char **args)
{
	int		option;
	int		i;

	option = 0;
	i = -1;
	if (ft_count_good_flags(args) >= 1)
		option = 1;
	if (ft_count_wrong_flags(args) >= 1)
		return (-1);
	if (strncmp("echo\0", args[0], 4) == 0)
		i++;
	while (args[i])
	{
		if (strncmp("-", args[i], 1))
			i++;
		else
			break ;
	}
	while (args[i])
		printf("%s ", args[i++]);
	if (option == 0)
		printf("\n");
	return (0);
}
