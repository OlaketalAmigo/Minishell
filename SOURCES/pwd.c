/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:47:15 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/29 14:23:03 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args)
{
	char	*cwd;
	int		status;

	status = 0;
	cwd = NULL;
	if (args[1] && args[1][0] == 45)
	{
		printf("pwd: invalid option: %s\n", args[1]);
		status = 2;
	}
	else
	{
		cwd = getcwd(cwd, 100);
		printf("%s\n", cwd);
		free(cwd);
	}
	return (status);
}

int	ft_pwd_pipe(t_struct *data, t_args *arg, char **args, char **path)
{
	char	*cwd;
	int		status;

	status = 0;
	cwd = NULL;
	if (args[1] && args[1][0] == 45)
	{
		printf("pwd: invalid option: %s\n", args[1]);
		status = 2;
	}
	else
	{
		cwd = getcwd(cwd, 100);
		printf("%s\n", cwd);
		free(cwd);
	}
	ft_free_child(args, data, arg, path);
	exit(status);
}
