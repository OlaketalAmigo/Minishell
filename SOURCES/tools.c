/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:36:54 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/05 14:26:14 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*string;
	int		k;

	k = -1;
	string = malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!string)
		return (NULL);
	while (++k < ft_strlen(s1))
		string[k] = s1[k];
	k = -1;
	while (++k < ft_strlen(s2))
		string[ft_strlen(s1) + k] = s2[k];
	string[ft_strlen(s1) + k] = '\0';
	free(s1);
	free(s2);
	return (string);
}
