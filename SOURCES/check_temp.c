/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_temp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehe <hehe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:39:04 by gprunet           #+#    #+#             */
/*   Updated: 2025/01/07 01:37:03 by hehe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_case(char *cmd, t_struct *data, char **args)
{
	if (data->last > 0 && data->i == 0)
	{
		if (ft_strncmp(cmd, "cat", 3) == 1)
		{
			if (args[0] == NULL)
				return (1);
		}
		if (ft_strncmp(cmd, "grep", 4) == 1)
		{
			if (args[0] != NULL)
				return (1);
		}
	}
	return (0);
}

int	count_puts(char *temp)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (temp[i])
	{
		if (temp[i] == '>' || temp[i] == '<')
		{
			i++;
			while (temp[i] == ' ' || temp[i] == '\t')
				i++;
			if (temp[i] && temp[i] != '>' && temp[i] != '<')
				nb++;
		}
		else
			i++;
	}
	printf("nb = %d\n", nb);
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

	temp = *full;
	*full = ft_strjoin(temp, line);
	free(temp);
}

int	puts_pos(char *full)
{
	int	i;

	i = 0;
	while (full[i])
	{
		if (i + 3 < ft_strlen(full))
		{
			if (full[i] == '>' && full[i + 1] == '>' && full[i + 2] == '>')
				return (1);
			else if (full[i] == '<' && full[i + 1] == '<' && full[i + 2] == '<')
				return (1);
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
	printf("r_nb = %d\n", r_nb);
	if (count_puts(full) < r_nb || puts_pos(full))
	{
		free(full);
		data->stop = 1;
		return (1);
	}
	free(full);
	return (0);
}
