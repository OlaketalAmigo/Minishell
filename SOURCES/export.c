/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:46:09 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/08 17:52:26 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ok_1(char *args)
{
	if (ft_isalpha(args[0]) != 1)
	{
		return (0);
	}
	return (1);
}

int	ft_ok_2(char *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i] && args[i] != 61)
	{
		if ((args[i] >= 0 && args[i] <= 47)
			|| (args[i] >= 58 && args[i] <= 64)
			|| (args[i] >= 91 && args[i] <= 96)
			|| (args[i] == 126))
		{
			return (0);
		}
		i++;
	}
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
	int	status;

	int (i) = 0;
	status = 0;
	if (args[1])
	{
		while (args[++i])
		{
			if (ft_ok_2(args[i]) == 1 && ft_ok_1(args[i]) == 1)
			{
				if (ft_ok_3(args[i]) == 1)
					ft_export_add_or_update(data, args, i);
				else
					continue ;
			}
			else
			{
				status = 1;
				ft_write_error(" not a valid identifier\n");
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
			if (ft_ok_2(args[i]) == 1 && ft_ok_1(args[i]) == 1)
			{
				if (ft_ok_3(args[i]) == 1)
					ft_export_add_or_update(data, args, i);
				else
					continue ;
			}
			else if (++status != 4)
				ft_write_error(" not a valid identifier\n");
		}
	}
	else
		ft_export_printf_ordered(data);
	ft_free_child(args, data, arg, path);
	exit(status);
}
