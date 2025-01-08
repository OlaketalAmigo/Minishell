/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utilis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:53:15 by hehe              #+#    #+#             */
/*   Updated: 2025/01/08 18:00:07 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection_cmd(char *arg)
{
	if (ft_strchr(arg, '>') == 1 || ft_strchr(arg, '<') == 1)
	{
		if (arg[0] == '>' || arg[0] == '<')
			return (0);
		return (1);
	}
	return (0);
}

char	*ft_strstr(char *str, char *find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str || !find)
		return (NULL);
	while (str[i])
	{
		if (str[i] == find[0])
		{
			j = 0;
			while (str[i + j] && find[j] && str[i + j] == find[j])
				j++;
			if (find[j] == '\0')
				return (&str[i]);
		}
		i++;
	}
	return (NULL);
}

void	command2_utilis(char **temp, t_args *a, int *i, int j)
{
	int	k;

	k = 0;
	if (!temp[*i][j] && temp[*i + 2])
		(*a).input[(*a).c_in] = ft_strdup(temp[*i + 2]);
	else
	{
		(*a).input[(*a).c_in] = malloc(sizeof(char) * ft_strlen(temp[*i]) + 1);
		while (temp[*i][j + k])
		{
			(*a).input[(*a).c_in][k] = temp[*i][j + k];
			k++;
		}
		(*a).input[(*a).c_in][k] = '\0';
	}
	*i = *i + 1;
}

void	close_word(t_args *args, char **temp, int *i, int j)
{
	int	k;

	k = 0;
	if (!temp)
		return ;
	(*args).output[(*args).c_out] = malloc(ft_strlen(temp[*i]) - j + 1);
	while (temp[*i][j + k])
	{
		(*args).output[(*args).c_out][k] = temp[*i][j + k];
		k++;
	}
	(*args).output[(*args).c_out][k] = '\0';
	*i = *i + 1;
}

void	command1_utilis(char **temp, t_args *new_args, int *i, int j)
{
	if (check_append(temp[*i]) == 1)
		(*new_args).append = 1;
	if (j >= ft_strlen(temp[*i]) && *i < ft_tablen(temp))
	{
		if (temp[*i + 2][0] == '>' && temp[*i + 4])
		{
			(*new_args).output[(*new_args).c_out] = ft_strdup(temp[*i + 4]);
			*i = *i + 5;
		}
		else if (temp[*i + 2])
		{
			(*new_args).output[(*new_args).c_out] = ft_strdup(temp[*i + 2]);
			*i = *i + 3;
		}
	}
	else
		close_word(new_args, temp, &(*i), j);
}
