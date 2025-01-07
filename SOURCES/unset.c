/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:12:14 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/12/13 14:52:23 by tfauve-p         ###   ########.fr       */
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
	str = malloc ((i + 2) * 1);
	while (++j < i)
		str[j] = args[j];
	str[j] = 61;
	str[++j] = '\0';
	return (str);
}

void	ft_delete_tab_case(t_struct *data, int i, int a, int b)
{
	char	**tab;
	int		j;

	j = ft_nb_arg(data->env);
	tab = malloc ((j) * 8);
	if (!tab)
		return ;
	while (++a < j)
	{
		if (a == i)
			b = 1;
		else
		{
			if (!tab)
				return (ft_free(tab));
			tab[a - b] = ft_put_string_to_tab(data, tab, (a - b), a);
		}
	}
	tab[a - b] = NULL;
	ft_free(data->env);
	data->env = tab;
}

int	ft_unset_main(t_struct *data, char *str)
{
	int		i;
	int		j;
	int		a;
	int		b;

	i = 0;
	j = 0;
	a = -1;
	b = 0;
	while (data->env[j])
	{
		if (ft_strncmp(str, data->env[j], ft_strlen(str)) == 1)
		{
			ft_delete_tab_case(data, i, a, b);
			break ;
		}
		i++;
		j++;
	}
	free(str);
	return (0);
}

int	ft_unset(t_struct *data, char **args)
{
	int		i;
	char	*str;

	i = 0;
	if (args[1])
	{
		while (args[++i])
		{
			str = ft_str_with_equal(args[i]);
			if (!str)
				return (1);
			if (ft_strcmp(str, "?=") == 0)
			{
				free(str);
				continue ;
			}
			ft_unset_main(data, str);
		}
	}
	return (0);
}

int	ft_unset_pipe(t_struct *data, t_args **arg, char **args, char **path)
{
	int		i;
	char	*str;

	i = 0;
	if (args[1])
	{
		while (args[++i])
		{
			str = ft_str_with_equal(args[i]);
			printf("str = %s\n", str);
			if (!str)
				return (1);
			if (ft_strcmp(str, "?=") == 0)
			{
				free(str);
				continue ;
			}
			ft_unset_main(data, str);
			free(str);
		}
	}
	ft_free_child(args, data, arg, path);
	exit(0);
}
