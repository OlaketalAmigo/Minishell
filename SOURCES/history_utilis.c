/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:29:05 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/05 14:26:33 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_read_line(int fd, char **stock)
{
	int			i;
	char		*line;

	line = malloc ((sizeof(char)) * (BUFFER_SIZE + 1));
	if (!line)
		return (0);
	i = read(fd, line, BUFFER_SIZE);
	if (i == -1 || i == 0)
	{
		free(line);
		return (i);
	}
	line[i] = '\0';
	*stock = ft_strjoin_gnl(*stock, line);
	return (i);
}

char	*get_next_line(int fd)
{
	static char	*stock = NULL;
	char		*line;
	int			x;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	x = 1;
	while (ft_strchr_gnl(stock, '\n') == 0)
	{
		x = ft_read_line(fd, &stock);
		if (x == 0)
			break ;
		if (x == -1)
			return (NULL);
	}
	line = ft_to_return(stock);
	stock = ft_to_keep(stock);
	return (line);
}

char	*ft_to_keep(char *string)
{
	int		i;
	int		k;
	char	*newstring;

	i = 0;
	k = 0;
	if (!string)
		return (NULL);
	while (string[i] != '\0' && string[i] != '\n')
		i++;
	newstring = malloc (sizeof(char) * (ft_strlen(string) - i + 1));
	if (!newstring)
		return (NULL);
	while (string[i++] != '\0')
		newstring[k++] = string[i];
	newstring[k] = '\0';
	if (ft_strchr_gnl(string, '\n') == 1)
		free(string);
	if (newstring[0] == '\0')
	{
		free(newstring);
		return (NULL);
	}
	return (newstring);
}

char	*ft_to_return(char *string)
{
	int		i;
	int		j;
	char	*newstring;

	i = 0;
	j = -1;
	if (!string)
		return (NULL);
	while (string[i] != '\0' && string[i] != '\n')
		i++;
	if (i == ft_strlen(string))
		return (string);
	newstring = malloc (sizeof(char) * (i + 2));
	if (!newstring)
		return (NULL);
	while (string[++j] != '\n')
		newstring[j] = string[j];
	newstring[j] = '\n';
	newstring[j + 1] = '\0';
	return (newstring);
}
