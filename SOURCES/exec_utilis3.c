/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utilis3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:36:49 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/19 11:03:00 by tfauve-p         ###   ########.fr       */
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] == s2[i] && s1[i] && s2[i])
			i++;
		else
			return (-1);
	}
	return (0);
}

int	ft_check_function(t_struct *data, char **args, char **true_path)
{
	if (!args)
		return (-1);
	if (ft_strncmp(args[0], "echo", 4) == 0)
		return (ft_echo(args));
	else if (ft_strncmp(args[0], "export", 4) == 0)
		return (-1);
	else if (ft_strncmp(args[0], "unset", 4) == 0)
		return (-1);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (-1);
	else if (ft_strncmp(args[0], "cd", 4) == 0)
		return (-1);
	else if (ft_strncmp(args[0], "env", 4) == 0)
		return (-1);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		return (-1);
	else
		return (execve(true_path[0], args, data->env))
}