/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:04:41 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/08 16:52:03 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_printf_ordered(t_struct *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < ft_nb_arg(data->env))
	{
		j = i + 1;
		while (j < ft_nb_arg(data->env))
		{
			if (ft_strcmp(data->env[j], data->env[k]) < 0)
				k = j;
			j++;
		}
		data->env = ft_swap(data, i, k);
		i++;
	}
	ft_printf_parsing(data->env);
}

int	ft_export(t_struct *data, char **args)
{
	int		i;
	char	*str;

	printf("started builtin export\n");
	i = 0;
	if (args[1])
	{
		while (args[++i])
		{
			str = ft_str_until_equal(args[i]);
			if (ft_search(str, data->env) == 1)
				ft_export_update(data, args[i]);
			else
				ft_export_add(data, args[i]);
			free(str);
		}
	}
	else
		ft_export_printf_ordered(data);
	return (0);
}

int	ft_export_pipe(t_struct *data, t_args *arg, char **args, char **path)
{
	char	**tab;

	printf("started builtin export pipe\n");
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
