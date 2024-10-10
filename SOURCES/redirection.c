#include "minishell.h"

char	*check_next(char **temp, int *i, char *c)
{
	char	*str;
	int		len;

	str = ft_strstr(temp[*i], c);
	len = ft_strlen(str);
	if (str[len - 1] == c[0])
	{
		str = ft_strdup(temp[*i + 2]);
		*i = *i + 3;
		return (str);
	}
	if (str[len - 1] != c[0])
	{
		str = ft_strdup(&str[1]);
		*i = *i + 1;
		return (str);
	}
	return (NULL);
}

int	separate_command2(char **temp, t_args *new_args, int *i)
{
	int	j;
	int	k;

	if (!(*new_args).cmd)
		(*new_args).cmd = malloc(sizeof(char) * ft_strlen(temp[*i]) + 1);
	if (!(*new_args).cmd)
		return (0);
	j = 0;
	k = 0;
	while (temp[*i][j] != '<')
	{
		new_args->cmd[j] = temp[*i][j];
		j++;
	}
	new_args->cmd[j] = '\0';
	j++;
	if (!temp[*i][j])
		(*new_args).input = ft_strdup(temp[*i + 2]);
	else
	{
		(*new_args).input = malloc(sizeof(char) * ft_strlen(temp[*i]) + 1);
		while (temp[*i][j + k])
		{
			(*new_args).input[k] = temp[*i][j + k];
			k++;
		}
		(*new_args).input[k] = '\0';
	}
	*i = *i + 1;
	return (1);
}

int	separate_command(char **temp, t_args *new_args, int *i, int *args)
{
	int	j;
	int	k;

	if (!(*new_args).cmd)
		(*new_args).cmd = malloc(sizeof(char) * ft_strlen(temp[*i]) + 1);
	(*new_args).args[0] = malloc(sizeof(char) * ft_strlen(temp[*i]) + 1);
	if (!(*new_args).cmd)
		return (0);
	j = 0;
	k = 0;
	while (temp[*i][j] != '>')
	{
		new_args->args[0][j] = temp[*i][j];
		j++;
	}
	new_args->args[0][j] = '\0';
	*args = *args + 1;
	k = 0;
	j++;
	if (check_append(temp[*i]) == 1)
		(*new_args).append = 1;
	if (!temp[*i][j])
	{
		(*new_args).output = ft_strdup(temp[*i + 2]);
		*i = *i + 3;
	}
	else
	{
		(*new_args).output = malloc(sizeof(char) * ft_strlen(temp[*i]) + 1);
		while (temp[*i][j + k])
		{
			(*new_args).output[k] = temp[*i][j + k];
			k++;
		}
		(*new_args).output[k] = '\0';
		*i = *i + 1;
	}
	(*new_args).out = 1;
	return (1);
}

int	check_redirection(char **temp, t_args *new_args, int *i, int *j)
{
	if (ft_strchr(temp[*i], '<') == 1 && temp[*i][0] != '<')
		return (separate_command2(temp, new_args, &(*i)));
	if (ft_strchr(temp[*i], '>') == 1 && temp[*i][0] != '>')
		return (separate_command(temp, new_args, &(*i), &(*j)));
	if (ft_strchr(temp[*i], '<') == 1)
	{
		(*new_args).input = check_next(temp, &(*i), "<");
		return (1);
	}
	if (ft_strchr(temp[*i], '>') == 1)
	{
		(*new_args).out = 1;
		if (check_append(temp[*i]) == 1)
		{
			(*new_args).output = check_next(temp, &(*i), ">>");
			(*new_args).append = 1;
			return (1);
		}
		(*new_args).output = check_next(temp, &(*i), ">");
		(*new_args).append = 0;
		return (1);
	}
	return (0);
}
