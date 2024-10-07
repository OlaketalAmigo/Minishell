/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:01:01 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/07 16:01:19 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_until_equal(char *args)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = -1;
	while (args[i] && args[i] != 61)
		i++;
	str = malloc ((i + 1) * 1);
	while (++j < i)
		str[j] = args[j];
	str[j] = '\0';
	return (str);
}

int	ft_search(char *str, char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if (ft_strcmp(tab[i], str) == 0)
			return (1);
	}
	return (-1);
}

void	ft_export_add(t_struct *data, char *args)
{
	char	**tab;
	
	tab = malloc (((ft_nb_arg(data->env)) + 2) * 8);
	if (!tab)
		return ;
	tab = ft_replace_tab(data->env, tab, args);
	ft_free(data->env);
	data->env = tab;
	ft_free(tab);
}

void	ft_export_update(t_struct *data, char *args)
{
	char	**tab;
	
	tab = malloc (16);
	tab[0] = args;
	tab[1] = NULL;
	ft_unset(data, tab);
	ft_export_add(data, args);
	ft_free(tab);
}