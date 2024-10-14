/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:47:15 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/14 15:59:44 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args)
{
	int		i;
	char	*cwd;

	i = ft_nb_arg(args);
	cwd = NULL;
	if (i == 1)
	{
		cwd = getcwd(cwd, 100);
		printf("%s\n", cwd);
		free(cwd);
	}
	else if (i != 1)
	{
		if (args[1][0] == 45)
			printf("pwd: bad option: %s\n", args[1]);
		else
			printf("pwd: too many arguments\n");
		return (-1);
	}
	return (0);
}

int	ft_pwd_pipe(t_struct *data, t_args *arg, char **args, char **path)
{
	int		i;
	char	*cwd;

	i = ft_nb_arg(args);
	cwd = NULL;
	if (i == 1)
	{
		cwd = getcwd(cwd, 100);
		printf("%s\n", cwd);
		free(cwd);
	}
	else if (i != 1)
	{
		if (args[1][0] == 45)
			printf("pwd: bad option: %s\n", args[1]);
		else
			printf("pwd: too many arguments\n");
		return (-1);
	}
	ft_free_child(args, data, arg, path);
	exit(EXIT_SUCCESS);
}
