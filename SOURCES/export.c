/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:04:41 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/05 12:51:06 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_free(tab);
	return (new_tab);
}

int	ft_export(t_struct *data, char **args)
{
	char	**tab;

	printf("started builtin export\n");
	if (args[1])
	{
		tab = malloc (((ft_nb_arg(data->env)) + 2) * 8);
		if (!tab)
			return (0);
		tab = ft_replace_tab(data->env, tab, args[1]); // douteux
		data->env = tab;
	}
	// else // printf un tas de trucs dans l'ordre
	return (0);
}

int	ft_export_pipe(t_struct *data, t_args *arg, char **args, char **path)
{
	char	**tab;

	printf("started builtin export\n");
	if (args[1])
	{
		tab = malloc (((ft_nb_arg(data->env)) + 2) * 8);
		if (!tab)
			return (0);
		tab = ft_replace_tab(data->env, tab, args[1]); // douteux
		data->env = tab;
	}
	// else // printf un tas de trucs dans l'ordre
	ft_free_child(args, data, arg, path);
	exit(EXIT_SUCCESS);
}
