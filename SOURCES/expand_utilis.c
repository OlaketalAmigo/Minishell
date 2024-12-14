/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:57:58 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/23 15:16:31 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_copy_tab(char *s)
{
	int		i;
	int		j;
	char	*new;

	i = ft_strlen(s);
	j = -1;
	new = malloc ((i + 1) * 1);
	if (!new)
		return (s);
	while (s[++j])
	{
		new[j] = s[j];
	}
	new[j] = '\0';
	free(s);
	return (new);
}

int	ft_countword_expand(char const *s, char c)
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
		if ((s[i] == c || s[i] == 36 || s[i] == 39) && dq > 0)
			j++;
		if (s[i + 1] == '\0')
			j++;
		i++;
	}
	if (j == 0 && s[i] == '\0')
		j++;
	return (j);
}

char	**ft_mecanism_expand(int length, char **tab, char *line, char c)
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
		if (line[i] != '\0' && j == -1)
			j = i;
		if (((line[i] == 36 || line[i] == 39 || line[i] == c
					|| line[i] == '\0') && j >= 0) && dq > 0)
		{
			tab[z++] = ft_writeword(line, j, i);
			j = i;
		}
	}
	tab[z] = NULL;
	return (tab);
}

char	**ft_split_expand(char *s, char c)
{
	char	**word_list;
	int		length;

	length = ft_strlen(s);
	word_list = malloc (sizeof(char *) * (ft_countword_expand(s, c) + 1));
	if (!word_list)
		return (NULL);
	word_list = ft_mecanism_expand(length, word_list, s, c);
	return (word_list);
}
