/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:19:16 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/18 12:30:32 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_full_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == 32 || str[i] == 9 || str[i] == 10))
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	ft_check(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	ft_start(char const *s1, char const *set)
{
	int	x;

	x = 0;
	while (ft_check(s1[x], set) == 0)
		x++;
	return (x);
}

int	ft_end(char const *s1, char const *set, int length)
{
	int	y;

	y = length - 1;
	while (ft_check(s1[y], set) == 0)
		y--;
	return (y);
}

char	*ft_strtrim(char const *s1, char *set)
{
	char	*string;
	int		debut;
	int		fin;
	int		i;
	int		length;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	length = ft_strlen(s1);
	debut = ft_start(s1, set);
	fin = ft_end(s1, set, length);
	if (fin - debut + 1 <= 0)
		string = malloc(1);
	else
		string = malloc (fin - debut + 2);
	if (!string)
		return (NULL);
	while (debut <= fin)
		string[i++] = s1[debut++];
	string[i] = '\0';
	return (string);
}
