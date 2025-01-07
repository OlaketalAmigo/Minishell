/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:53:48 by hehe              #+#    #+#             */
/*   Updated: 2025/01/07 15:37:29 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_fd(int fd, t_args *arg)
{
	if (arg->m_out > 0)
	{
		if (arg->append)
			fd = open(arg->output[arg->c_out], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(arg->output[arg->c_out], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(arg->output[arg->c_out]);
			return (-1);
		}
	}
	else if (arg->m_in > 0)
		fd = open(arg->input[arg->c_in], O_RDONLY);
	if (fd < 0)
	{
		perror(arg->input[arg->c_in]);
		return (-1);
	}
	if (arg->cmd[0] == '>' && arg->cmd[1] != '>')
	{
		close(fd);
		return (-1);
	}
	return (fd);
}

char	*check_next(char **temp, int *i, char *c, t_args *n_args)
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
		// free(str);
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

int	check_redirection(char **temp, t_args *n_args, int *i, int *j)
{
	if (temp[*i][0] == '<' && temp[*i][1] == '<')
		return (check_heredoc(temp, n_args, &(*i)));
	(*n_args).put = 1;
	if (ft_strchr(temp[*i], '<') == 1 && temp[*i][0] != '<')
		return (separate_command2(temp, n_args, &(*i)));
	if (ft_strchr(temp[*i], '>') == 1 && temp[*i][0] != '>')
		return (separate_command(temp, n_args, &(*i), &(*j)));
	if (ft_strchr(temp[*i], '<') == 1 && check_pos(temp[*i], '<', n_args) == 1)
	{
		(*n_args).input[(*n_args).c_in] = check_next(temp, &(*i), "<", &(*n_args));
		return (1);
	}
	if (ft_strchr(temp[*i], '>') == 1 && check_pos(temp[*i], '>', n_args) == 1)
	{
		(*n_args).b_output = 1;
		if (check_append(temp[*i]) == 1)
		{
			(*n_args).output[(*n_args).c_out] = check_next(temp, &(*i), ">>", &(*n_args));
			return (1);
		}
		if (get_cmd(temp, &(*i), n_args) != 1)
			else_command(n_args, temp, &(*i));
		return (1);
	}
	return (0);
}
