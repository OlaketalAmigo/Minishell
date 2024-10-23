/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:01:42 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/23 15:37:01 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_search_expand(char *str, char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if (ft_strncmp(tab[i], str, ft_strlen(str)) == 1)
			return (1);
	}
	return (-1);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int	ft_export_add_or_update(t_struct *data, char **args, int i)
{
	char	*str;

	str = ft_str_with_equal(args[i]);
	if (ft_search(str, data->env) == 1)
		ft_export_update(data, args[i]);
	else
		ft_export_add(data, args[i]);
	free(str);
	return (0);
}

int	ft_unset_export(t_struct *data, char **args)
{
	int	i;

	i = 0;
	if (args[1])
	{
		while (args[++i])
		{
			ft_unset_main(data, args[i]);
		}
	}
	return (0);
}
