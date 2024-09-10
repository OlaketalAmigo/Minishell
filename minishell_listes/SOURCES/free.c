/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:06:49 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/10 14:38:16 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}


void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*i;

	while (lst != 0 && *lst != 0)
	{
		i = (*lst)->next_content;
		ft_lstdelone(*lst, del);
		*lst = i;
	}
	*lst = NULL;
}

void	free_nodes(t_list **stack)
{
	int	i = 0;
	t_list	*temp;
	t_list	*current;

	if (!stack)
		return ;
	current = *stack;
	while (current)
	{
		printf("i = %d\n", i);
		temp = current->next_content;
		free(current);
		current = temp;
		i++;
	}
	*stack = NULL;
}
