/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehe <hehe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:53:48 by hehe              #+#    #+#             */
/*   Updated: 2024/12/16 21:32:55 by hehe             ###   ########.fr       */
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
	if (str[len - 1] == c[0])
	{
		str = ft_strdup(temp[*i + 2]);
		*i = *i + 3;
		return (str);
	}
	if (str[len - 1] != c[0])
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
	j = 0;
	while (temp[*i][j] != '<')
	{
		new_args->cmd[j] = temp[*i][j];
		j++;
	}
	new_args->cmd[j] = '\0';
	j++;
	command2_utilis(temp, new_args, i, j);
	return (1);
}

int	separate_command(char **temp, t_args *new_args, int *i, int *args)
{
	int	j;

	if (!(*new_args).cmd)
		(*new_args).cmd = malloc(sizeof(char) * ft_strlen(temp[*i]) + 1);
	(*new_args).args[0] = malloc(sizeof(char) * ft_strlen(temp[*i]) + 1);
	if (!(*new_args).cmd)
		return (0);
	j = 0;
	while (temp[*i][j] != '>')
	{
		new_args->args[0][j] = temp[*i][j];
		j++;
	}
	new_args->args[0][j] = '\0';
	*args = *args + 1;
	j++;
	command1_utilis(temp, new_args, i, j);
	return (1);
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

int	get_cmd(char **temp, int *i, t_args *args)
{
	int		j;
	int		tab_len;

	if ((*args).cmd)
		return (0);
	j = 1;
	tab_len = ft_tablen(temp);
	if (!temp[*i][j])
	{
		(*args).output = ft_strdup(temp[*i + 2]);
		*i = *i + 4;
	}
	else
	{
		(*args).output = get_cmd_output(temp[*i]);
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

int	check_redirection(char **temp, t_args *new_args, int *i, int *j)
{
	if (temp[*i][0] == '<' && temp[*i][1] == '<')
		return (check_heredoc(temp, new_args, &(*i)));
	if (ft_strchr(temp[*i], '<') == 1 && temp[*i][0] != '<')
		return (separate_command2(temp, new_args, &(*i)));
	if (ft_strchr(temp[*i], '>') == 1 && temp[*i][0] != '>')
		return (separate_command(temp, new_args, &(*i), &(*j)));
	if (ft_strchr(temp[*i], '<') == 1)
	{
		(*new_args).input = check_next(temp, &(*i), "<");
		return (1);
	}
	if (ft_strchr(temp[*i], '>') == 1)
	{
		if (check_append(temp[*i]) == 1)
		{
			(*new_args).output = check_next(temp, &(*i), ">>");
			(*new_args).append = 1;
			return (1);
		}
		if (get_cmd(temp, &(*i), new_args) == 1)
			return (1);
		if ((*new_args).output)
			free((*new_args).output);
		(*new_args).output = check_next(temp, &(*i), ">");
		(*new_args).append = 0;
		return (1);
	}
	return (0);
}
