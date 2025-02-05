/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utilis3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:36:49 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/08 19:45:05 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_cleared(char *s, char c)
{
	char	**word_list;
	int		length;

	length = ft_strlen(s);
	word_list = malloc (sizeof(char *) * (ft_countword(s, c) + 1));
	if (!word_list)
		return (NULL);
	word_list = ft_mecanism(length, word_list, s, c);
	word_list = ft_clear_to_function(word_list);
	return (word_list);
}

int	clean_fail(t_struct *data)
{
	if (data->input || data->heredoc)
		close(data->saved_stdin);
	if (data->output)
	{
		close(data->pipefd[1]);
		close(data->pipefd[0]);
	}
	return (127);
}

int	ft_execve(char **path, char **args, t_struct *data)
{
	int	result;

	if (!path || !path[0])
		return (clean_fail(data));
	if (data->total > 1 && data->i < data->last)
		close(data->pipefd[0]);
	if (data->temp_fd != -1)
		close(data->temp_fd);
	if (data->input || data->heredoc)
		close(data->saved_stdin);
	if (data->output)
		close(data->saved_stdout);
	result = execve(path[0], args, data->env);
	perror("execve errror");
	return (result);
}

int	ft_function_pipe(t_struct *d, char **args, char **path, t_args **arg)
{
	if (!args)
		return (-1);
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo_pipe(d, arg, args, path));
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export_pipe(d, arg, args, path));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset_pipe(d, arg, args, path));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd_pipe(d, arg, args, path));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd_pipe(d, arg, args, path));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env_pipe(d, arg, args, path));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit_pipe(d, arg, args, path));
	return (ft_execve(path, args, d));
}

int	ft_check_function(t_struct *d, char **args, char **path, t_args **arg)
{
	if (!args)
		return (-1);
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(d, args));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(d, args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(d, args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(d));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(d, arg, args, path));
	d->pid = fork();
	if (d->pid == -1)
		return (-2);
	if (d->pid == 0)
		return (ft_execve(path, args, d));
	waitpid(d->pid, &d->status, 0);
	return (0);
}
