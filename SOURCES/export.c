/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:04:41 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/12/18 08:34:46 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ok(char *args)
{
	int	i;

	i = 0;
	while (args[i] && args[i] == 32)
	{
		i++;
	}
	if (ft_isalpha(args[i]) != 1 || args[i] == 61)
		return (0);
	return (1);
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
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (args[1])
	{
		while (args[++i])
		{
			if (ft_ok(args[i]) == 1)
				ft_export_add_or_update(data, args, i);
			else
			{
				status = 1;
				printf("export: not a valid identifier");
			}
		}
	}
	else
		ft_export_printf_ordered(data);
	return (status);
}

int	ft_export_pipe(t_struct *data, t_args **arg, char **args, char **path)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (args[1])
	{
		while (args[++i])
		{
			if (ft_ok(args[i]) == 1)
				ft_export_add_or_update(data, args, i);
			else
			{
				status = 1;
				printf("export: `%s': not a valid identifier\n", args[i]);
			}
		}
	}
	else
		ft_export_printf_ordered(data);
	ft_free_child(args, data, arg, path);
	exit(status);
}
