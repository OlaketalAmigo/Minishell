/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehe <hehe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:53:48 by hehe              #+#    #+#             */
/*   Updated: 2025/01/07 23:36:01 by hehe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_fd(int fd, t_args *a)
{
	if (a->m_out > 0 && a->c_out < a->m_out)
	{
		if (a->append)
			fd = open(a->output[a->c_out], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(a->output[a->c_out], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(a->output[a->c_out]);
			return (-1);
		}
	}
	else if (a->m_in > 0 && a->c_in < a->m_in)
		fd = open(a->input[a->c_in], O_RDONLY);
	if (fd < 0)
	{
		perror(a->input[a->c_in]);
		return (-1);
	}
	if (a->cmd[0] == '>' && a->cmd[1] != '>')
	{
		close(fd);
		return (-1);
	}
	return (fd);
}

char	*check_n(char **temp, int *i, char *c, t_args *n_args)
{
	char	*ret;
	char	*str;

	str = ft_strstr(temp[*i], c);
	if (c[0] == '>' && c[1] == '>')
		(*n_args).append = 1;
	else if (c[0] == '>')
		(*n_args).b_output = 1;
	else if (c[0] == '<')
		(*n_args).b_input = 1;
	if (str[ft_strlen(str) - 1] == c[0] && *i + 2 < ft_tablen(temp))
	{
		ret = ft_strdup(temp[*i + 2]);
		*i = *i + 3;
		return (ret);
	}
	if (str[ft_strlen(str) - 1] != c[0])
	{
		ret = ft_strdup(&str[1]);
		*i = *i + 1;
		return (ret);
	}
	return (NULL);
}

int	separate_command2(char **temp, t_args *new_args, int *i)
{
	int	j;

	if (!(*new_args).cmd)
		(*new_args).cmd = malloc(sizeof(char) * ft_strlen(temp[*i]) + 1);
	if (!(*new_args).cmd)
		return (0);
	j = sort_redir(temp[*i], new_args, '<', 2);
	j++;
	command2_utilis(temp, new_args, i, j);
	(*new_args).b_input = 1;
	return (1);
}

int	separate_command(char **temp, t_args *new_args, int *i, int *args)
{
	int	j;

	if (!(*new_args).cmd)
	{
		(*new_args).cmd = malloc(sizeof(char) * ft_strlen(temp[*i]) + 1);
		(*new_args).cmd[0] = '\0';
	}
	(*new_args).args[0] = malloc(sizeof(char) * ft_strlen(temp[*i]) + 1);
	if (!(*new_args).cmd)
		return (0);
	j = sort_redir(temp[*i], new_args, '>', 1);
	*args = *args + 1;
	j++;
	command1_utilis(temp, new_args, i, j);
	(*new_args).b_output = 1;
	return (1);
}

int	check_redirection(char **temp, t_args *n_a, int *i, int *j)
{
	if (temp[*i][0] == '<' && temp[*i][1] == '<')
		return (check_heredoc(temp, n_a, &(*i)));
	(*n_a).put = 1;
	if (ft_strchr(temp[*i], '<') == 1 && temp[*i][0] != '<')
		return (separate_command2(temp, n_a, &(*i)));
	if (ft_strchr(temp[*i], '>') == 1 && temp[*i][0] != '>')
		return (separate_command(temp, n_a, &(*i), &(*j)));
	if (ft_strchr(temp[*i], '<') == 1 && check_pos(temp[*i], '<', n_a) == 1)
	{
		(*n_a).input[(*n_a).c_in] = check_n(temp, &(*i), "<", &(*n_a));
		return (1);
	}
	if (ft_strchr(temp[*i], '>') == 1 && check_pos(temp[*i], '>', n_a) == 1)
	{
		(*n_a).b_output = 1;
		if (check_append(temp[*i]) == 1)
		{
			(*n_a).output[(*n_a).c_out] = check_n(temp, &(*i), ">>", &(*n_a));
			return (1);
		}
		if (get_cmd(temp, &(*i), n_a) != 1)
			else_command(n_a, temp, &(*i));
		return (1);
	}
	return (0);
}
