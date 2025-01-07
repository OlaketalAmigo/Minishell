/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:34:40 by gprunet           #+#    #+#             */
/*   Updated: 2025/01/07 11:48:15 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	else_command(t_args *args, char **temp, int *i)
{
	if ((*args).output[(*args).c_out])
		free((*args).output[(*args).c_out]);
	(*args).output[(*args).c_out] = check_next(temp, &(*i), ">", &(*args));
	(*args).append = 0;
}

int	sort_redir(char *temp, t_args *new_args, char c, int com)
{
	int (i) = 0;
	if (com == 1)
	{
		while (temp[i])
		{
			if (temp[i] == c && i == (*new_args).pos_redir)
				break ;
			(*new_args).args[0][i] = temp[i];
			i++;
		}
		(*new_args).args[0][i] = '\0';
		return (i);
	}
	else
	{
		while (temp[i])
		{
			if (temp[i] == c && i == new_args->pos_redir)
				break ;
			(*new_args).cmd[i] = temp[i];
			i++;
		}
		(*new_args).cmd[i] = '\0';
		return (i);
	}
}

char	*get_cmd_output(char *temp)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	while (temp[i] != '>')
		i++;
	i++;
	j = ft_strlen(temp);
	res = malloc(j - i + 1);
	j = 0;
	while (i < ft_strlen(temp))
		res[j++] = temp[i++];
	res[j] = '\0';
	return (res);
}

void	eos_case(t_args *args, char **temp, int *i)
{
	if ((*i + 2) >= ft_tablen(temp))
		return ;
	if (temp[*i + 2][0] != '>')
	{
		if ((*args).output[(*args).c_out])
			free((*args).output[(*args).c_out]);
		(*args).output[(*args).c_out] = ft_strdup(temp[*i + 2]);
		*i = *i + 4;
	}
	else
	{
		if (*i + 4 >= ft_tablen(temp))
			return ;
		if ((*args).output[(*args).c_out])
			free((*args).output[(*args).c_out]);
		(*args).output[(*args).c_out] = ft_strdup(temp[*i + 4]);
		*i = *i + 6;
	}
}

int	get_cmd(char **temp, int *i, t_args *args)
{
	int		j;
	int		tab_len;

	if ((*args).cmd)
		return (0);
	j = 1;
	tab_len = ft_tablen(temp);
	if (!temp[*i][j])
		eos_case(args, temp, &(*i));
	else
	{
		(*args).output[(*args).c_out] = get_cmd_output(temp[*i]);
		*i = *i + 2;
	}
	if (*i >= tab_len)
		(*args).cmd = ft_strdup(">");
	else
		(*args).cmd = ft_strdup(temp[*i]);
	(*args).append = 0;
	*i = *i + 1;
	return (1);
}
