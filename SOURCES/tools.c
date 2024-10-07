/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:36:54 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/07 16:03:50 by tfauve-p         ###   ########.fr       */
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

char	**ft_replace_tab(char **tab, char **new_tab, char *new)
{
	int		j;
	int		k;

	j = -1;
	while (tab[++j])
	{
		k = -1;
		new_tab[j] = malloc ((ft_strlen(tab[j]) + 1) * 1);
		if (!new_tab)
			return (NULL);
		while (tab[j][++k])
			new_tab[j][k] = tab[j][k];
		new_tab[j][k] = '\0';
	}
	k = -1;
	new_tab[j] = malloc ((ft_strlen(new) + 1) * 1);
	if (!new_tab)
		return (NULL);
	while (new[++k])
		new_tab[j][k] = new[k];
	new_tab[j][k] = '\0';
	new_tab[j + 1] = NULL;
	return (new_tab);
}

void	ft_swap(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = s2;
	s2 = tmp;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (s1[i])
	{
		if (s1[i] == s2[i])
			i++;
		else if (s1[i] > s2[i])
			return (1);
		else
			return (-1);
	}
	if (s2[i])
		return (-1);
	return (0);
}