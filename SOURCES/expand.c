/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:08:06 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/08 18:32:10 by tfauve-p         ###   ########.fr       */
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
			while (data->env[i][k] != 61 && data->env[i][k])
				k++;
			new = malloc ((ft_strlen(data->env[i]) - k + 1) * 1);
			if (!new)
				return (s);
			while (++j != -4 && data->env[i][k] && data->env[i][++k])
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

	i = 0;
	new = malloc (ft_strlen(s) + 1);
	if (!new)
		return (NULL);
	while (s[++i])
			new[i - 1] = s[i];
	new[i - 1] = 61;
	new[++i - 1] = '\0';
	if (ft_search_expand(new, data->env) == 1)
	{
		new = ft_get_from_env(data, new);
		return (free(s), new);
	}
	else if (ft_strcmp(s, "$") != 0)
	{
		free(new);
		new = malloc (2);
		new[0] = 32;
		new[1] = '\0';
		return (free(s), new);
	}
	return (s);
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
	int		i;
	int		j;
	int		k;
	char	**new;
	char	**tab;

	k = -1;
	new = malloc ((ft_nb_arg(data->arg) + 1) * 8);
	i = -1;
	if (!new)
		return ;
	while (data->arg[++i])
	{
		tab = ft_split_expand(data->arg[i], 32);
		tab = ft_expand_replace(data, tab);
		j = -1;
		new[i] = NULL;
		while (tab[++j])
			new[i] = ft_strjoin_gnl(new[i], tab[j]);
		free(tab);
	}
	new[i] = NULL;
	ft_free(data->arg);
	data->arg = new;
}
