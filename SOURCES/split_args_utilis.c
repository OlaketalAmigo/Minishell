/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utilis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:33:51 by gprunet           #+#    #+#             */
/*   Updated: 2024/10/07 12:40:34 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	ft_check_path(t_struct *data, char *arg)
{
	char	**tab;
	char	*tmp;
	int		i;

	i = 0;
	tab = NULL;
	while (data->path[i] && arg)
	{
		tmp = ft_strjoin(data->path[i], arg);
		if (ft_strchr(tmp, ' ') == 1)
			tab = check_access(tmp, 1);
		else if (access(tmp, X_OK) == 0)
			tab = check_access(tmp, 0);
		free(tmp);
		if (tab)
			break ;
		i++;
	}
	if (tab)
	{
		ft_free(tab);
		return (1);
	}
	return (0);
}

int	c_args(char **temp, t_struct *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (temp[i])
	{
		if (ft_strchr(temp[i], '|') == 0 && is_empty(temp[i]) == 0)
		{
			if ((i > 1 && ft_check_path(data, temp[i - 2])))
				count++;
			else if (!ft_check_path(data, temp[i]))
				count++;
		}
		i++;
	}
	return (count);
}

int	ft_check_hard_path(t_struct *data, char *arg)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split(arg, '/');
	while (tab[i])
	{
		if (ft_check_path(data, tab[i]) && !tab[i + 1])
		{
			ft_free(tab);
			return (1);
		}
		i++;
	}
	ft_free(tab);
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

int	count_commands(char **arg, t_struct *data)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		//printf("arg[%d] = %s\n", i, arg[i]);
		if (check_redirection_cmd(arg[i]) == 1)
		{
			count++;
			i++;
			continue ;
		}
		if (ft_strchr(arg[i], '/') == 1)
		{
			if (ft_check_hard_path(data, arg[i]))
				count++;
		}
		else if (is_empty(arg[i]) == 0)
		{
			if (ft_check_builtins(arg[i]) == 1 || ft_strchr(arg[i], '|') == 1)
				count++;
			else if (ft_check_path(data, arg[i]))
				count++;
		}
		i++;
	}
	return (count);
}

int	ft_check_cmd(t_args *new_args, int i, char *str)
{
	if (i > 0 && (*new_args).cmd == NULL && str == NULL)
	{
		free((*new_args).args);
		(*new_args).args = NULL;
		return (1);
	}
	if ((*new_args).cmd == NULL && str)
	{
		free((*new_args).args);
		(*new_args).args = NULL;
		return (1);
	}
	return (0);
}

int	verif_command(t_struct *data, char **cmd, t_args *new_args)
{
	char	**tab;

	tab = NULL;
	if (new_args->cmd != NULL)
		return (0);
	if (ft_strchr(*cmd, '/') == 1)
	{
		if (ft_check_hard_path(data, *cmd))
		{
			tab = ft_split(*cmd, '/');
			free(*cmd);
			*cmd = ft_strdup(tab[ft_tablen(tab) - 1]);
			ft_free(tab);
			return (1);
		}
	}
	if (ft_check_builtins(*cmd) == 1 || ft_strchr(*cmd, '|') == 1)
		return (1);
	else if (ft_check_path(data, *cmd))
		return (1);
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

int	check_append(char *temp)
{
	if (ft_strstr(temp, ">>"))
		return (1);
	return (0);
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

t_args	ft_assign_args(t_args *new_args, char **temp, t_struct *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (temp[i])
	{
		if (check_redirection(temp, new_args, &i, &j) == 1)
			continue ;
		if (!(*new_args).cmd && check_built(temp[0], new_args, &i) == 1)
			continue ;
		if (ft_check_cmd(new_args, i, NULL) == 1)
			break ;
		if (check_string(temp[i], &i) == 1)
			continue ;
		if (verif_command(data, &temp[i], new_args) == 1)
			(*new_args).cmd = ft_strdup(temp[i]);
		else if ((*new_args).cmd && check_redirection(temp, new_args, &i, &j) == 0)
			(*new_args).args[j++] = ft_strdup(temp[i]);
		else if (ft_check_cmd(new_args, i, "free") == 1)
			break ;
		i++;
	}
	if ((*new_args).args)
		(*new_args).args[j] = NULL;
	return (*new_args);
}
