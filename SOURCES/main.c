/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:11 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/08/06 11:55:26 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*a;
	
	a = NULL;
	while(1)
	{
		a = readline("minishell->");
		if (a)
		{
			printf("a = %s\n", a);
			free(a);
			continue;
		}
		break;
	}
	return (0);
}