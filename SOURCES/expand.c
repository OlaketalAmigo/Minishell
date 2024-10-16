/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:08:06 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/16 16:44:11 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_expand_join(char **tab, int j)
{
	char	**new_tab;
	int		i;
	int		k;

	i = -1;
	k = -1;
	new_tab = malloc ((j + 1) * 8);
	printf("j = %d\n", j);
	if (!new_tab)
		return (NULL);
	i = -1;
	while (tab[++k])
	{
		if (ft_strncmp(tab[k], "$", 1) == 1)
		{
			new_tab[++i] = ft_strjoin_gnl(tab[k], tab[k + 1]);
			k++;
		}
		else
			new_tab[++i] = tab[k];
	}
	new_tab[++i] = NULL;
	free(tab);
	return (new_tab);
}

char	*ft_get_from_env(t_struct *data, char *s)
{
	int		i;
	int		j;
	int		k;
	char	*new;

	i = -1;
	j = -1;
	k = 0;
	new = NULL;
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], s, ft_strlen(s)) == 1)
		{
			while (data->env[i][k] != 61)
				k++;
			new = malloc ((ft_strlen(data->env[i]) - k) * 1);
			if (!new)
				return (s);
			while (data->env[i][++k] && ++j != -4)
				new[j] = data->env[i][k];
			new[j] = '\0';
		}
	}
	free(s);
	return (new);
}

char	*ft_expanded(t_struct *data, char *s)
{
	char	*new;
	int		i;

	i = -1;
	new = malloc (ft_strlen(s) + 1);
	if (!new)
		return (NULL);
	while (s[i])
	{
		if (i != 0)
			new[i - 1] = s[i];
	}
	new[i] = 61;
	new[++i] = '\0';
	if (ft_search_expand(new, data->env) == 1)
	{
		new = ft_get_from_env(data, new);
		return (free(s), new);
	}
	else
		return (free(new), s);
}

char	**ft_expand_replace(t_struct *data, char **tab)
{
	int		i;
	char	**new_tab;

	i = -1;
	new_tab = malloc ((ft_nb_arg(tab) + 1) * 8);
	if (!new_tab)
		return (NULL);
	while (tab[++i])
	{
		if (ft_strncmp(tab[i], "$", 1) == 1)
			new_tab[i] = ft_expanded(data, tab[i]);
		else
			new_tab[i] = ft_copy_tab(tab[i]);
	}
	new_tab[i] = NULL;
	i = -1;
	free(tab);
	return (new_tab);
}

void	ft_expand(t_struct *data)
{
	char	**tab;
	char	**new_tab;
	int		i;
	int		j;

	i = -1;
	j = 0;
	tab = ft_split_expand(data->line, 32);
	while (tab[++i])
		if (ft_strncmp(tab[i], "$", 1) == 1)
			j++;
	// ICI TOUT EST NIQUEL
	new_tab = ft_expand_join(tab, (ft_nb_arg(tab) - j));
	tab = ft_expand_replace(data, new_tab);
	i = -1;
	while (tab[++i])
		data->line = ft_strjoin_gnl(data->line, tab[i]);
	free(tab);
}
