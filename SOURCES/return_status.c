/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:58:06 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/29 14:45:42 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_update(t_struct *data, char *args)
{
	char	**tab;

	tab = malloc (3 * 8);
	if (tab)
	{
		tab[0] = "unset";
		tab[1] = ft_str_until_equal(args);
		tab[2] = NULL;
		ft_unset_export(data, tab);
		ft_export_add(data, args);
		free(tab[1]);
		free(tab);
	}
}

int	ft_negative(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

int	ft_dizaine(long nombre)
{
	int	i;

	i = 0;
	while (nombre > 9)
	{
		nombre = nombre / 10;
		i++;
	}
	i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		i;
	long	nombre;

	i = 0;
	nombre = n;
	if (ft_negative(n) == 1)
	{
		i++;
		nombre = nombre * (-1);
	}
	i = i + ft_dizaine(nombre);
	number = malloc(i + 1);
	if (!number)
		return (NULL);
	number[i] = '\0';
	while (nombre >= 10)
	{
		number[i-- - 1] = (nombre % 10) + 48;
		nombre = nombre / 10;
	}
	number[i - 1] = (nombre % 10) + 48;
	if (ft_negative(n) == 1)
		number[0] = '-';
	return (number);
}

int	ft_update_return_status(t_struct *data, int j)
{
	char	*status;
	char	*tmp;

	tmp = ft_itoa(j);
	if (!tmp)
		return (0);
	status = ft_strjoin("?=", tmp);
	if (!status)
	{
		free(tmp);
		return (0);
	}
	ft_export_update(data, status);
	free(status);
	return (0);
}
