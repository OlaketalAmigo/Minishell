/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:53:12 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/09/19 11:07:39 by tfauve-p         ###   ########.fr       */
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
	char	**flags;
	char	**cmds;
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

// MAIN //

void	ft_main(int g_sig_receiver, t_struct *data);

// PARSER //

void	ft_printf_parsing(char **tab);
int		ft_parser(t_struct *data);

// PARSER UTILIS //

void	ft_error_parsing(void);
int		ft_nb_arg(char **tab);

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

void	ft_exec(t_struct *data);

// EXEC UTILIS //

char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
int		ft_strchr(char *s, char c);
int		is_empty(char *arg);
int		is_flag(char *arg);

//EXEC UTILIS 2 //

void	ft_free_child(char **args, t_struct *data);
void	free_flags(char **flags);
void	ft_fill_new_args(char **new_args, char ***flags, char ***cmds);
char	**check_access(char *tmp, int s);
int		ft_hard_path(char **arg);

// EXEC UTILIS 3 //

char	**ft_split_cleared(char *s, char c);
int	ft_check_function(t_struct *data, char **args, char **true_path);

// FREE //

void	ft_free_all(t_struct *data);
void	ft_free(char **tab);

// CLEAR TO FUNCTION	

int		ft_isalnum(int c);
char	*ft_replace(char *tab, int i);
char	**ft_clear(char **tab, int i, int dquote, int quote);
char	**ft_clear_to_function(char **tab);

// ECHO //

int		ft_is_flag(char *s);
int		ft_count_flags(char **tab);
char	**ft_fill_flags(char **args, char **flags);
int		ft_echo(char **args);

#endif