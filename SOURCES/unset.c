/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:12:14 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/07 15:59:17 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_with_equal(char *args)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = -1;
	while (args[i] && args[i] != 61)
		i++;
	if (args[i] == 61)
		i++;
	str = malloc ((i + 1) * 1);
	while (++j < i)
		str[j] = args[j];
	str[j] = '\0';
	return (str);
}

int	ft_unset(t_struct *data, char **args)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (args[i])
	{
		str = ft_str_with_equal(args[i]);
		j = 0;
		while (data->env[j])
		{
			if (ft_strncmp(str, data->env[j], ft_strlen(str)) == 0)
			{
				//ft_delete_tab_case(data, i);
				printf("delete case %d\n", i);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_unset_pipe(t_struct *data, t_args *arg, char **args, char **path)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (args[i])
	{
		str = ft_str_with_equal(args[i]);
		j = 0;
		while (data->env[j])
		{
			if (ft_strncmp(str, data->env[j], ft_strlen(str)) == 0)
			{
				//ft_delete_tab_case(data, i);
				printf("delete case %d\n", i);
				break ;
			}
			j++;
		}
		i++;
	}
	ft_free_child(args, data, arg, path);
	exit(EXIT_SUCCESS);
}
