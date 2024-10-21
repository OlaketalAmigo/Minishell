/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:01:42 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/21 15:12:24 by tfauve-p         ###   ########.fr       */
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
