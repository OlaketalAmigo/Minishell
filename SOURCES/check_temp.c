/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_temp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:39:04 by gprunet           #+#    #+#             */
/*   Updated: 2025/01/08 16:32:18 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_puts(char *temp, t_struct *data)
{
	int	i;
	int	nb;
	int	total;

	i = 0;
	nb = 0;
	total = 0;
	while (temp[i])
	{
		if (temp[i] == '>' || temp[i] == '<')
		{
			i++;
			while (temp[i] == ' ' || temp[i] == '\t' || temp[i] == '/')
			{
				i++;
			}
			if (temp[i] && temp[i] != '>' && temp[i] != '<'
				&& data->redir[total] == 1)
				nb++;
			total++;
		}
		else
			i++;
	}
	return (nb);
}

int	single_check(char *temp, t_struct *data, int *r_nb, int *nb)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (temp[i] == '>')
		{
			if (data->redir[*nb] == 1 && temp[i + 1] != '>')
				*r_nb = *r_nb + 1;
			*nb = *nb + 1;
		}
		else if (temp[i] == '<')
		{
			if (data->redir[*nb] == 1 && temp[i + 1] != '<')
				*r_nb = *r_nb + 1;
			*nb = *nb + 1;
		}
		i++;
	}
	return (0);
}

void	add_full(char *line, char **full)
{
	char	*temp;
	char	*temp2;

	temp = ft_strdup(*full);
	free(*full);
	temp2 = ft_strdup(line);
	*full = ft_strjoin_gnl(temp, temp2);
}

int	puts_pos(char *full, t_struct *data)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (full[i])
	{
		if (i + 3 < ft_strlen(full))
		{
			if (full[i] == '>' && full[i + 1] == '>' && full[i + 2] == '>')
			{
				if (data->redir[total] == 1)
					return (1);
				total++;
			}
			else if (full[i] == '<' && full[i + 1] == '<' && full[i + 2] == '<')
			{
				if (data->redir[total] == 1)
					return (1);
				total++;
			}
		}
		i++;
	}
	return (0);
}

int	temp_check(char **temp, t_struct *data, int time)
{
	char	*full;
	int		i;
	int		nb;
	int		r_nb;

	if (time > 0)
		return (0);
	i = -1;
	nb = 0;
	r_nb = 0;
	full = ft_strdup("");
	while (temp[++i])
	{
		add_full(temp[i], &full);
		single_check(temp[i], data, &r_nb, &nb);
	}
	if (count_puts(full, data) < r_nb || puts_pos(full, data))
	{
		free(full);
		data->stop = 1;
		return (1);
	}
	free(full);
	return (0);
}
