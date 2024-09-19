/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:27:45 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/19 10:41:54 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_flag(char *s)
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

int	ft_count_flags(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		if (ft_is_flag(tab[i]) == 1)
			j++;
		i++;
	}
	return (j);
}

char	**ft_fill_flags(char **args, char **flags)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i])
	{
		if (ft_is_flag(args[i]) == 1)
		{
			flags[j] = malloc(ft_strlen(args[i]) + 1);
			if (!flags)
				return (ft_free(flags), NULL);
			flags[j] = args[i];
			flags[ft_strlen(args[i])] = '\0';
			j++;
		}
		i++;
	}
	flags[j] = NULL;
	return (flags);
}

int	ft_echo(char **args)
{
	int		option;
	int		i;
	char	**flags;

	i = ft_count_flags(args);
	flags = malloc(8 * (i + 1));
	if (!flags)
		return (-1);
	flags = ft_fill_flags(args, flags);
	if (!flags)
		return (-1);
	while (args[++i])
		printf("%s ", args[i]);
	if (flags)
		option = 1;
	if (option == 0)
		printf("\n");
	ft_free(flags);
	return (0);
}
