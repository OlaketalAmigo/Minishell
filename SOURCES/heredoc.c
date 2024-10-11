#include "minishell.h"

char	*assign_delimiter(char *temp)
{
	int	i;

	i = 2;
	while (temp[i] && temp[i] == ' ')
		i++;
	if (!temp[i])
	{
		return (NULL);
	}
	return (ft_strdup(&temp[i]));
}

int	check_heredoc(char **temp, t_args *new_args, int *i)
{
	printf("temp[%d] = %s\n", *i, temp[*i]);
	if (temp[*i][0] == '<' && temp[*i][1] == '<')
	{
		if (temp[*i][2] == '\0' && (*i + 2) < ft_tablen(temp))
		{
			new_args->delimiter = ft_strdup(temp[*i + 2]);
			if (temp[*i + 3])
				*i = *i + 3;
		}
		else if (temp[*i][2] != '\0')
		{
			new_args->delimiter = assign_delimiter(temp[*i]);
				*i = *i + 1;
		}
		else
		{
			printf("Error: Missing delimiter\n");
			new_args->delimiter = malloc(sizeof(char) * 1);
			new_args->delimiter[0] = '\0';
			*i = *i + 1;
			return (0);
		}
	}
	if (new_args->delimiter)
		return (1);
	return (0);
}

int	ft_heredoc_pipe(t_args *arg, t_struct *data, char **args, char **path)
{
	char	*line;

	line = NULL;
	if (arg->delimiter[0] == '\0')
	{
		printf("Error: Missing delimiter\n");
		return (0);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (0);
		if (ft_strcmp(line, arg->delimiter) == 0)
		{
			free(line);
			break ;
		}
		printf("%s\n", line);
		free(line);
	}
	ft_free_child(args, data, arg, path);
	exit(EXIT_SUCCESS);
}

int	ft_heredoc(t_args *arg, int pipefd)
{
	char	*line;

	line = NULL;
	if (arg->delimiter[0] == '\0')
	{
		printf("Error: Missing delimiter\n");
		return (0);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (0);
		if (ft_strcmp(line, arg->delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd, line, ft_strlen(line));
		write(pipefd, "\n", 1);
		free(line);
	}
	return (1);
}
