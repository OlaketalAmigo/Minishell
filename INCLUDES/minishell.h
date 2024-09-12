/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:53:12 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/12 15:08:49 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "stdio.h"
# include "stdlib.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "asm/termbits.h"
# include "sys/ioctl.h"
# include "signal.h"
# include "unistd.h"
# include "fcntl.h"
# include "sys/types.h"
# include "sys/wait.h"

// COLORS //

# define P = "\033[0;35m"
# define LP = "\033[1;35m"
# define R = "\033[0;31m"
# define LR = "\033[1;31m"
# define O = "\033[0;33m"
# define Y = "\033[1;33m"
# define LG = "\033[1;32m"
# define G = "\033[0;32m"
# define LC = "\033[1;36m"
# define C = "\033[0;36m"
# define LB = "\033[1;34m"
# define B = "\033[0;34m"
# define RST = "\033[0;0m"

typedef struct data
{
	char	**arg;
	int		nb_arg;
	char	**tmp_arg;
	char	*line;
	char	**tab;
	char	**path;
	char	**env;
}	t_struct;

typedef struct list
{
	char		**content;
	struct list	*next_content;
}	t_list;

// SIGNALS //

# define SIG_INT = 1
# define SIG_QUIT = 2

// PARSER //

t_list	*ft_error_parsing(void);
t_list	*ft_parser(t_struct *data, t_list *parsing);

// PARSER UTILIS //

t_list	*ft_error_parsing(void);
int		ft_nb_arg(t_struct *data);
t_list	*ft_add_node(t_list **tab, char **arg);

// PARSER SPLIT //

int		ft_countword(char const *s, char c);
int		ft_strlen(char const *s);
char	*ft_writeword(char const *s, int start, int end);
char	**ft_mecanism(int length, char **tab, char *line, char c);
char	**ft_split(char *s, char c);

// PARSER TRIM

int		ft_check(char const c, char const *set);
int		ft_start(char const *s1, char const *set);
int		ft_end(char const *s1, char const *set, int length);
char	*ft_strtrim(char const *s1, char *set);
int		ft_full_space(char *str);

// PARSER LST //

t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char **content);

// PARSE CHECKER //

int		ft_parser_check_pipe_and(t_struct *data);
int		ft_skip_until(char *a, char b, int i);
int		ft_parser_check_quotes(t_struct *data);
int		ft_parser_check(t_struct *data);

// SIGNALS //

void	ft_init_signals(void);
void	ft_get_signal_int(int sig);
void	ft_get_signal_quit(int sig);
void	ft_handle_signals(void);

// EXEC //

void	ft_exec(t_list *parsing, t_struct *data);

// FREE //

void	ft_free(char **tab);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_free_lst(t_list *lst);
void	free_nodes(t_list **stack);

#endif