/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utilis3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:36:49 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/29 16:51:53 by gprunet          ###   ########.fr       */
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

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] && s2[i] && s1[i] == s2[i])
			i++;
		else
			return (-1);
	}
	return (1);
}

int	ft_execve(char **path, char **args, t_struct *data, t_args *arg)
{
	int	result;

	if (!path || !path[0])
	{
		printf("Command %s not found\n", arg->cmd);
		ft_free_child(args, data, arg, path);
		return (-1);
	}
	result = execve(path[0], args, data->env);
	perror("execve errror");
	return (result);
}

int	ft_function_pipe(t_struct *d, char **args, char **path, t_args **arg)
{
	if (!args)
		return (-1);
	if (ft_strncmp(args[0], "echo", 4) == 1)
		return (ft_echo_pipe(d, arg[d->i], args, path));
	else if (ft_strncmp(args[0], "export", 6) == 1)
		return (ft_export_pipe(d, arg[d->i], args, path));
	else if (ft_strncmp(args[0], "unset", 5) == 1)
		return (ft_unset_pipe(d, arg[d->i], args, path));
	else if (ft_strncmp(args[0], "pwd", 3) == 1)
		return (ft_pwd_pipe(d, arg[d->i], args, path));
	else if (ft_strncmp(args[0], "cd", 2) == 1)
		return (ft_cd_pipe(d, arg[d->i], args, path));
	else if (ft_strncmp(args[0], "env", 3) == 1)
		return (ft_env_pipe(d, arg[d->i], args, path));
	else if (ft_strncmp(args[0], "exit", 4) == 1)
		return (ft_exit_pipe(d, arg[d->i], args, path));
	return (ft_execve(path, args, d, arg[d->i]));
}

int	ft_check_function(t_struct *d, char **args, char **path, t_args **arg)
{
	if (!args)
		return (-1);
	if (ft_strncmp(args[0], "echo", 4) == 1)
		return (ft_echo(args));
	else if (ft_strncmp(args[0], "export", 6) == 1)
		return (ft_export(d, args));
	else if (ft_strncmp(args[0], "unset", 5) == 1)
		return (ft_unset(d, args));
	else if (ft_strncmp(args[0], "pwd", 3) == 1)
		return (ft_pwd(args));
	else if (ft_strncmp(args[0], "cd", 2) == 1)
		return (ft_cd(d, args));
	else if (ft_strncmp(args[0], "env", 3) == 1)
		return (ft_env(d));
	else if (ft_strncmp(args[0], "exit", 4) == 1)
		return (ft_exit(d, arg, args, path));
	d->pid = fork();
	if (d->pid == -1)
		return (-1);
	if (d->pid == 0)
		return (ft_execve(path, args, d, arg[d->i]));
	waitpid(d->pid, NULL, 0);
	return (0);
}
