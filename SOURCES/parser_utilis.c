/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:08:18 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/10 14:02:43 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_error_parsing(void)
{
	printf("Erreur d'entree\n");
	exit(EXIT_FAILURE);
}

int	ft_nb_arg(t_struct *data)
{
	int	i;

	i = 0;
	while (data->tmp_arg[i])
		i++;
	return (i);
}

void	ft_add_node(t_list **tab, char **arg)
{
	t_list	*new;

	new = ft_lstnew(arg);
	ft_lstadd_back(tab, new);
}
