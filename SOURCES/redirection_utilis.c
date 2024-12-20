/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utilis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehe <hehe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:53:15 by hehe              #+#    #+#             */
/*   Updated: 2024/12/19 20:08:57 by hehe             ###   ########.fr       */
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

void	command2_utilis(char **temp, t_args *new_args, int *i, int j)
{
	int	k;

	k = 0;
	if (!temp[*i][j] && temp[*i + 2])
		(*new_args).input = ft_strdup(temp[*i + 2]);
	else
	{
		(*new_args).input = malloc(sizeof(char) * ft_strlen(temp[*i]) + 1);
		while (temp[*i][j + k])
		{
			(*new_args).input[k] = temp[*i][j + k];
			k++;
		}
		(*new_args).input[k] = '\0';
	}
	*i = *i + 1;
}

void	close_word(t_args *args, char **temp, int *i, int j)
{
	int	k;

	k = 0;
	if (!temp)
		return ;
	(*args).output = malloc(ft_strlen(temp[*i]) - j + 1);
	while (temp[*i][j + k])
	{
		(*args).output[k] = temp[*i][j + k];
		k++;
	}
	(*args).output[k] = '\0';
	*i = *i + 1;
}

void	command1_utilis(char **temp, t_args *new_args, int *i, int j)
{
	if (check_append(temp[*i]) == 1)
		(*new_args).append = 1;
	if (j >= ft_strlen(temp[*i]))
	{
		if (temp[*i + 2][0] == '>' && temp[*i + 4])
		{
			(*new_args).output = ft_strdup(temp[*i + 4]);
			*i = *i + 5;
		}
		else if (temp[*i + 2])
		{
			(*new_args).output = ft_strdup(temp[*i + 2]);
			*i = *i + 3;
		}
	}
	else
		close_word(new_args, temp, &(*i), j);
}
