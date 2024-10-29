/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:28:07 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/29 14:22:43 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_countword(char const *s, char c)
{
	int (i) = 0;
	int (j) = 0;
	int (dq) = 1;
	int (q) = 1;
	while (s[i])
	{
		if (s[i] == 34 && q != -1)
			dq = -dq;
		if (s[i] == 39 && dq != -1)
			q = -q;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0' )
			&& dq > 0 && q > 0)
			j = j + 2;
		i++;
	}
	if (j == 0 && s[i] == '\0')
		j++;
	return (j);
}

int	ft_strlen(char const *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_writeword(char const *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc (1 + end - start);
	if (!word)
		return (NULL);
	while (start + i < end)
	{
		word[i] = s[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_mecanism(int length, char **tab, char *line, char c)
{
	int (i) = -1;
	int (j) = -1;
	int (z) = 0;
	int (dq) = 1;
	int (q) = 1;
	while (++i <= length)
	{
		if (line[i] == 34 && q != -1)
			dq = -dq;
		if (line[i] == 39 && dq != -1)
			q = -q;
		if (line[i] != '\0' && line[i] != c && j == -1)
			j = i;
		if (((line[i] == c || line[i] == '\0') && j >= 0)
			&& dq > 0 && q > 0)
		{
			tab[z++] = ft_writeword(line, j, i);
			if (line[i])
				tab[z++] = ft_writeword(line, i, i + 1);
			j = -1;
		}
	}
	tab[z] = NULL;
	return (tab);
}

char	**ft_split(char *s, char c)
{
	char	**word_list;
	int		length;

	length = ft_strlen(s);
	word_list = malloc (sizeof(char *) * (ft_countword(s, c) + 1));
	if (!word_list)
		return (NULL);
	word_list = ft_mecanism(length, word_list, s, c);
	return (word_list);
}
