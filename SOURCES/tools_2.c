/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:01:42 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/16 15:08:06 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_search_expand(char *str, char **tab)
{
	int	i;

	i = -1;
	printf("start search expand\n");
	while (tab[++i])
	{
		if (ft_strncmp(tab[i], str, ft_strlen(str)) == 1)
			return (1);
	}
	return (-1);
}
