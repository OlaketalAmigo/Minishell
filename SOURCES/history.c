/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:41:41 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/29 14:21:48 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_update_history(char *line)
{
	int	i;
	int	j;

	j = -1;
	i = open("history.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (i == -1)
	{
		printf("Couldn't update history\n");
		return ;
	}
	add_history(line);
	while (line[++j])
		ft_putchar_fd(line[j], i);
	close (i);
}

void	ft_set_up_history(void)
{
	char	*line;
	int		i;

	i = open("history.txt", O_RDONLY | O_CREAT, 0777);
	if (i == -1)
	{
		printf("Couldn't set up history\n");
		return ;
	}
	line = get_next_line(i);
	if (line)
		add_history(line);
	while (line)
	{
		free(line);
		line = get_next_line(i);
		if (line)
			add_history(line);
	}
	close (i);
}
