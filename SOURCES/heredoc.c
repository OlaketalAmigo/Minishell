/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehe <hehe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:11:06 by hehe              #+#    #+#             */
/*   Updated: 2024/10/21 13:25:15 by hehe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*assign_delimiter(char *temp, t_args *new_args)
{
	int	i;

	i = 2;
	while (temp[i] && temp[i] == ' ')
		i++;
	if (!temp[i])
		return (NULL);
	if (!new_args->cmd)
		new_args->cmd = ft_strdup("<<");
	return (ft_strdup(&temp[i]));
}

int	check_heredoc(char **temp, t_args *arg, int *i)
{
	if (temp[*i][0] == '<' && temp[*i][1] == '<')
	{
		if (temp[*i][2] == '\0' && (*i + 2) < ft_tablen(temp))
		{
			arg->delimiter = ft_strdup(temp[*i + 2]);
			if (!arg->cmd)
				arg->cmd = ft_strdup(temp[*i]);
			*i = *i + 3;
		}
		else if (temp[*i][2] != '\0')
		{
			arg->delimiter = assign_delimiter(temp[*i], arg);
			*i = *i + 1;
		}
		else
		{
			arg->delimiter = malloc(sizeof(char) * 1);
			arg->delimiter[0] = '\0';
			*i = *i + 1;
			return (1);
		}
		return (1);
	}
	return (0);
}

int	heredoc_algo(int pipefd, t_args *arg)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			perror("readline error");
			return (-1);
		}
		if (ft_strcmp(line, arg->delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd, line, ft_strlen(line));
		write(pipefd, "\n", 1);
		free(line);
	}
	return (0);
}

int	heredoc_pipe(t_struct *data)
{
	close(data->pipefd[1]);
	if (dup2(data->pipefd[0], 0) == -1)
	{
		perror("dup2 error");
		close(data->pipefd[0]);
		return (-1);
	}
	close(data->pipefd[0]);
	return (0);
}

int	ft_heredoc(t_args *arg, t_struct *data)
{
	if (arg->delimiter[0] == '\0')
	{
		printf("Error: Missing delimiter\n");
		return (-1);
	}
	data->saved_stdin = dup(0);
	if (data->saved_stdin == -1)
	{
		perror("dup error");
		return (-1);
	}
	if (pipe(data->pipefd) == -1)
	{
		perror("pipe error");
		return (-1);
	}
	if (heredoc_algo(data->pipefd[1], arg) == -1)
	{
		close(data->pipefd[1]);
		return (-1);
	}
	if (heredoc_pipe(data) == -1)
		return (-1);
	return (0);
}
