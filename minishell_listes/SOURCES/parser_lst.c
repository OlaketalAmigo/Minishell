/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:07:45 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/08/14 13:39:41 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next_content)
	{
		if (lst->next_content == NULL)
			return (lst);
		lst = lst->next_content;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*i;

	if (!new)
		return ;
	printf("content = %s\n", new->content[0]);
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	i = ft_lstlast(*lst);
	i->next_content = new;
}

t_list	*ft_lstnew(char **content)
{
	t_list	*new;

	new = (t_list *) malloc (sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next_content = NULL;
	return (new);
}
