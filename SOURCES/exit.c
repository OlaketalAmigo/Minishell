/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehe <hehe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:46:12 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/30 15:20:55 by hehe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_everything_digit(char	*args)
{
	int	i;
	int	k;
	int	plus;
	int	minus;

	i = -1;
	k = 0;
	plus = 0;
	minus = 0;
	while (args[++i])
	{
		if (args[i] >= 48 && args[i] <= 57 && k < 12)
			k++;
		else if (args[i] == 43)
			plus += 1;
		else if (args[i] == 45)
			minus += 1;
		else
			return (-1);
	}
	if (minus > 1 || plus > 1)
		return (printf("pog\n"), -1);
	return (printf("super\n"), 1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nb;
	int	sign;

	nb = 0;
	i = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		sign = -sign;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	return (nb * sign);
}

int	ft_exit(t_struct *data, t_args **arg, char **args, char **path)
{
	int	i;

	i = 0;
	if (ft_nb_arg(args) >= 3)
	{
		printf("exit: too many arguments\n");
		i = 1;
	}
	else 
	{
		if (args[1])
		{
			if (ft_is_everything_digit(args[1]) == 1)
				i = ft_atoi(args[1]);
			else
				printf("exit: %s: numeric argument required\n", args[1]);
		}
		ft_free(data->env);
		ft_free(data->arg);
		ft_free(data->path);
		ft_free(args);
		ft_free(path);
		ft_free_struct(arg, data->count);
		exit(i);
	}
	return (i);
}

int	ft_exit_pipe(t_struct *data, t_args **arg, char **args, char **path)
{
	int	i;

	i = 0;
	if (ft_nb_arg(args) >= 3)
	{
		printf("exit: too many arguments\n");
		i = 1;
	}
	else if (args[1])
	{
		if (ft_is_everything_digit(args[1]) == 1)
			i = ft_atoi(args[1]);
		else
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			i = 2;
		}
	}
	ft_free_child(args, data, arg, path);
	exit(i);
}
