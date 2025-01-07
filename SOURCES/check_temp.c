/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_temp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:39:04 by gprunet           #+#    #+#             */
/*   Updated: 2025/01/07 16:02:50 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_fds(t_args *arg, t_struct *data)
{
	int	fd;
	int	total;

	fd = 0;
	total = arg->m_in + arg->m_out;
	while (total != 0)
	{
		fd = check_fd(fd, arg);
		if (arg->c_out > 0 && arg->c_out < arg->m_out)
			arg->c_out++;
		else if (arg->c_in > 0 && arg->c_in < arg->m_in)
			arg->c_in++;
		if (fd < 0)
		{
			data->status = 1;
			data->stop = 1;
			ft_update_return_status(data, 1);
			return (1);
		}
		close(fd);
		total--;
	}
	return (0);
	
}

int	special_case(char *cmd, t_struct *data, char **args, t_args *arg)
{
	if (check_fds(arg, data) == 1)
		return (1);
	arg->c_in = 0;
	arg->c_out = 0;
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
	if (count_puts(full) < r_nb || puts_pos(full))
	{
		free(full);
		data->stop = 1;
		return (1);
	}
	free(full);
	return (0);
}
