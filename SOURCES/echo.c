/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:27:45 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/18 12:18:20 by tfauve-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_char(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!input)
		return (0);
	while (input[i])
	{
		if (input[i] != 34 && input[i] != 39)
			count++;
		i++;
	}
	return (count);
}

char	*ft_remove_shit(char *input)
{
	char	**tab;
	char	*replace;
	int		i;
	int		j;
	int		k;

	tab = ft_split(input, " ");
	i = 0;
	while (tab[i])
	{
		j = 0;
		k = 0;
		replace = malloc (ft_count_char(tab[i]) + 1);
		while (tab[i][j])
		{
			if (tab[i][j] != 34 && tab[i][j] != 39)
				replace[k++] = tab[i][j];
			j++;
		}
		free(tab[i]);
		i++;
	}
	return (tab);
}

int	ft_echo(char *input)
{
	int		option;
	char	*output;

	option = 0;
	output = ft_remove_shit(input);
	printf("%s", output);
	if (option == 0)
		printf("\n");
	free(output);
	return (0);
}
