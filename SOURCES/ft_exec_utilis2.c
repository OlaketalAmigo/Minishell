/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utilis2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:07:19 by gprunet           #+#    #+#             */
/*   Updated: 2025/01/08 17:28:50 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	doc_count(char *f, char c, t_struct *data)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	if (ft_strlen(f) < 3)
		return (0);
	while (f[i] && f[i] != '|')
	{
		if (i == 0)
		{
			if (f[i] == '<' && f[i + 1] == '<' && f[i + 2] != '<')
				nb = nb + 1;
		}
		else if (i > 0 && f[i] == '<' && f[i - 1] == '<' && f[i + 1] != '<')
			nb = nb + 1;
		i++;
	}
	if (nb > 0)
		data->heredoc = 1;
	if (c == '<')
		return (nb);
	return (0);
}

int	get_max(char **temp, char c, int current, t_struct *data)
{
	char	*full;
	int		i;
	int		nb;
	int		t_redir;

	full = ft_strdup("");
	i = 0;
	nb = 0;
	t_redir = 0;
	while (current < ft_tablen(temp))
	{
		add_full(temp[current], &full);
		current++;
	}
	while (full[i] && full[i] != '|')
	{
		if (full[i] == c && full[i + 1] != c && data->redir[t_redir] == 1)
			nb++;
		if (full[i] == '<' || full[i] == '>')
			t_redir++;
		i++;
	}
	nb = nb - doc_count(full, c, data);
	free(full);
	return (nb);
}

void	init_puts(t_args *args)
{
	int	i;

	i = 0;
	if ((*args).m_in <= 0)
	{
		free((*args).input);
		(*args).input = NULL;
	}
	else
	{
		while (i <= (*args).m_in && (*args).input)
			(*args).input[i++] = NULL;
	}
	i = 0;
	if ((*args).m_out <= 0)
	{
		free((*args).output);
		(*args).output = NULL;
	}
	else
	{
		while (i <= (*args).m_out)
			(*args).output[i++] = NULL;
	}
}

int	c_puts(char **temp, char c, t_struct *data)
{
	int	i;
	int	j;
	int	real_redir;
	int	count;

	i = 0;
	count = 0;
	real_redir = 0;
	while (temp[i])
	{
		j = 0;
		while (temp[i][j])
		{
			if (temp[i][j] == c)
			{
				if (data->redir[count] == 1)
					real_redir++;
				count++;
			}
			j++;
		}
		i++;
	}
	return (real_redir);
}

char	**ft_fill_args(char *cmds, char **args)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	while (args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	i = 0;
	j = 1;
	if (cmds)
	{
		new_args[i] = ft_strdup(cmds);
		while (args[i])
			new_args[j++] = ft_strdup(args[i++]);
	}
	new_args[j] = NULL;
	return (new_args);
}
