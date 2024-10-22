/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:04:41 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/22 16:04:09 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ok_for_export(char *args)
{
	int	i;
	int	q;
	int	dq;

	q = 1;
	dq = 1;
	i = -1;
	while (args[++i])
	{
		if (args[i] == 34 && q != -1)
			dq = -dq;
		if (args[i] == 39 && dq != -1)
			q = -q;
		if (args[i] == 61 && q == 1 && dq == 1)
			return (1);
	}
	return (-1);
}

int	ft_ok_for_export2(char *args)
{
	int	i;

	i = 0;
	while (args[i] && ft_isalpha(args[i]) == 1)
		i++;
	if (i == 0)
		return (-1);
	return  (1);
}

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

	i = 0;
	if (args[1])
	{
		while (args[++i])
		{
			if (ft_ok_for_export(args[i]) == 1 && ft_ok_for_export2(args[i]) == 1)
			{
				str = ft_str_with_equal(args[i]);
				if (ft_search(str, data->env) == 1)
					ft_export_update(data, args[i]);
				else
					ft_export_add(data, args[i]);
				free(str);
			}
		}
	}
	else
		ft_export_printf_ordered(data);
	return (0);
}

int	ft_export_pipe(t_struct *data, t_args *arg, char **args, char **path)
{
	int		i;
	char	*str;

	i = 0;
	if (args[1])
	{
		while (args[++i])
		{
			if (ft_ok_for_export(args[i]) == 1)
			{
				str = ft_str_with_equal(args[i]);
				if (ft_search(str, data->env) == 1)
					ft_export_update(data, args[i]);
				else
					ft_export_add(data, args[i]);
				free(str);
			}
		}
	}
	else
		ft_export_printf_ordered(data);
	ft_free_child(args, data, arg, path);
	exit(EXIT_SUCCESS);
}
