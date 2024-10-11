#include "minishell.h"

int	check_append(char *temp)
{
	if (ft_strstr(temp, ">>") != NULL)
		return (1);
	return (0);
}

int	check_redirection_cmd(char *arg)
{
	if (ft_strchr(arg, '>') == 1 || ft_strchr(arg, '<') == 1)
	{
		if (arg[0] == '>' || arg[0] == '<')
			return (0);
		return (1);
	}
	return (0);
}

char	*ft_strstr(char *str, char *find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str || !find)
		return (NULL);
	while (str[i])
	{
		if (str[i] == find[0])
		{
			j = 0;
			while (str[i + j] && find[j] && str[i + j] == find[j])
				j++;
			if (find[j] == '\0')
				return (&str[i]);
		}
		i++;
	}
	return (NULL);
}
