#include "minishell.h"

char	*assign_delimiter(char *temp, t_args *new_args)
{
	int	i;

	i = 2;
	while (temp[i] && temp[i] == ' ')
		i++;
	if (!temp[i])
		return (NULL);
	if (!new_args->cmd)
		new_args->cmd = ft_strdup("<<");
	return (ft_strdup(&temp[i]));
}

int	check_heredoc(char **temp, t_args *new_args, int *i)
{
	if (temp[*i][0] == '<' && temp[*i][1] == '<')
	{
		if (temp[*i][2] == '\0' && (*i + 2) < ft_tablen(temp))
		{
			new_args->delimiter = ft_strdup(temp[*i + 2]);
			if (!new_args->cmd)
				new_args->cmd = ft_strdup(temp[*i]);
			*i = *i + 3;
			return (1);
		}
		else if (temp[*i][2] != '\0')
		{
			new_args->delimiter = assign_delimiter(temp[*i], new_args);
			*i = *i + 1;
			return (1);
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
	return (0);
}

int	ft_heredoc_pipe(t_args *arg, t_struct *data, char **args, char **path)
{
	char	*line;

	line = NULL;
	if (arg->delimiter[0] == '\0')
	{
		printf("Error: Missing delimiter\n");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (-1);
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

int	heredoc_algo(int pipefd, t_args *arg)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			perror("readline error");
			return (-1);
		}
		if (ft_strcmp(line, arg->delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd, line, ft_strlen(line));
		write(pipefd, "\n", 1);
		free(line);
	}
	return (0);
}

int	ft_heredoc(t_args *arg, t_struct *data)
{
	int	pipefd[2];
	int	end;

	end = 0;
	if (arg->delimiter[0] == '\0')
	{
		printf("Error: Missing delimiter\n");
		return (-1);
	}
	data->saved_stdin = dup(0);
	if (pipe(pipefd) == -1)
	{
		perror("pipe error");
		return (-1);
	}
	end = heredoc_algo(pipefd[1], arg);
	printf("end = %d\n", end);
	close(pipefd[1]);
	if (end == -1)
	{
		close(pipefd[0]);
		return (-1);
	}
	if (dup2(pipefd[0], 0) == -1)
	{
		perror("dup2 error");
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[0]);
	return (end);
}
