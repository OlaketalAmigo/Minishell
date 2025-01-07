/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:53:48 by hehe              #+#    #+#             */
/*   Updated: 2024/12/19 02:17:08 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_fd(int fd, t_args *arg)
{
	if (arg->output)
	{
		if (arg->append)
			fd = open(arg->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(arg->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(arg->output);
			return (-1);
		}
	}
	else
		fd = open(arg->input, O_RDONLY);
	if (fd < 0)
	{
		perror(arg->input);
		return (-1);
	}
	if (arg->cmd[0] == '>' && arg->cmd[1] != '>')
	{
		close(fd);
		return (-1);
	}
	return (fd);
}

char	*check_next(char **temp, int *i, char *c)
{
	char	*str;
	int		len;

	str = ft_strstr(temp[*i], c);
	len = ft_strlen(str);
	if (str[len - 1] == c[0] && temp[*i + 2])
	{
		str = ft_strdup(temp[*i + 2]);
		*i = *i + 3;
		return (str);
	}
	if (str[len - 1] != c[0] && temp[*i])
	{
		str = ft_strdup(&str[1]);
		*i = *i + 1;
		return (str);
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
	return (1);
}

int	check_redirection(char **temp, t_args *n_args, int *i, int *j)
{
	if (temp[*i][0] == '<' && temp[*i][1] == '<')
		return (check_heredoc(temp, n_args, &(*i)));
	if (ft_strchr(temp[*i], '<') == 1 && temp[*i][0] != '<')
		return (separate_command2(temp, n_args, &(*i)));
	if (ft_strchr(temp[*i], '>') == 1 && temp[*i][0] != '>')
		return (separate_command(temp, n_args, &(*i), &(*j)));
	if (ft_strchr(temp[*i], '<') == 1 && check_pos(temp[*i], '<', n_args) == 1)
	{
		(*n_args).input = check_next(temp, &(*i), "<");
		return (1);
	}
	if (ft_strchr(temp[*i], '>') == 1 && check_pos(temp[*i], '>', n_args) == 1)
	{
		if (check_append(temp[*i]) == 1)
		{
			(*n_args).output = check_next(temp, &(*i), ">>");
			(*n_args).append = 1;
			return (1);
		}
		if (get_cmd(temp, &(*i), n_args) == 1)
			return (1);
		else_command(n_args, temp, &(*i));
		return (1);
	}
	return (0);
}
