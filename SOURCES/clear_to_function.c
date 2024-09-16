/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_to_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:36:26 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/16 12:16:31 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 97 && c <= 122)
		return (1);
	else
		return (0);
}

char	*ft_replace(char *tab, int i)
{
	int		j;
	int		k;
	char	*str;

	j = 0;
	k = 0;
	str = malloc (ft_strlen(tab));
	if (!str)
		return (NULL);
	while (tab[j])
	{
		if (j != i)
		{
			str[k] = tab[j];
			k++;
		}
		j++;
	}
	free(tab);
	str[k] = '\0';
	return (str);
}

char	**ft_clear_to_function(char  **tab)
{
	int	i;
	int	j;
	int	(dquote) = 1;
	int	(quote) = 1;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			printf("character actuel : %c, dq = %d, q = %d\n", tab[i][j], dquote, quote);
			if (tab[i][j] == 34 && quote > 0)
			{
				printf("degage\n");
				tab[i] = ft_replace(tab[i], j);
				j = j - 1;
				dquote = -dquote;
				continue ;
			}
			if (tab[i][j] == 39 && dquote > 0)
			{
				printf("degage\n");
				tab[i] = ft_replace(tab[i], j);
				j = j - 1;
				quote = -quote;
				continue ;
			}
			if (tab[i][j] == '\0') // PROBLEME '""' Retour sur condition
				break ;
			j++;
		}
		i++;
	}
	return (tab);
}
