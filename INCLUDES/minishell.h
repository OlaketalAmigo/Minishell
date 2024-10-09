/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfauve-p <tfauve-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:53:12 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/07 15:59:28 by tfauve-p         ###   ########.fr       */
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

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
	int		pipefd[2];
	int		in_fd;
	int		out_fd;
	char	**env;
	int		launched_env;
	int		saved_stdout;
	int		saved_stdin;
	pid_t	pid;
}	t_struct;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	*input;
	char	*output;
	int		append;
	int		in;
	int		out;
}	t_args;

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

// SET UP ENV //

int		ft_set_up_env(t_struct *data);

// SIGNALS //

void	ft_init_signals(void);
void	ft_get_signal_int(int sig);
void	ft_get_signal_quit(int sig);
void	ft_handle_signals(void);

// EXEC //

void	ft_exec(t_struct *data);
int		split_args(char **arg, t_args **new_args, t_struct *data);
void	handle_redirection(t_args *arg, t_struct *data, char **path, char **args);

// FT EXEC UTILIS //

void	ft_check_i(int i, int cmd_count, t_struct *data);
void	ft_2nd_exec(t_struct *data, char **args, char **true_path);
char	**ft_assign_path(t_struct *data, char *cmd);
void	ft_exec_init(t_struct *data, t_args **arg, int *cmd_count);

// EXEC UTILIS //

char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
int		ft_strchr(char *s, char c);
int		is_empty(char *arg);
int		is_flag(char *arg);

//EXEC UTILIS 2 //

void	ft_free_child(char **args, t_struct *data, t_args *arg, char **path);
void	ft_fill_new_args(char **arg, t_args *full_arg);
char	**check_access(char *tmp, int s);
int		ft_hard_path(char *arg);
int		ft_check_builtins(char *arg);
char	**ft_true_path(t_struct *data, char *cmd);

// EXEC UTILIS 3 //ma

char	**ft_split_cleared(char *s, char c);
int		ft_check_function_pipe(t_struct *d, char **args, char **path, t_args *arg);
int		ft_check_function(t_struct *d, char **args, char **path, t_args *arg);
int		ft_strncmp(char *s1, char *s2, int n);

// SPLIT ARGS UTILIS //

int		c_args(char **temp, t_struct *data);
int		count_commands(char **arg, t_struct *data);
t_args	ft_assign_args(t_args *new_args, char **temp, t_struct *data);

// ASSIGN ARGS UTILIS //

int		check_built(char *temp, t_args *new_args, int *i);
int		check_string(char *temp, int *i);

// FREE //

void	ft_free_struct(t_args **arg, int cmd_count);
void	ft_free_all(t_struct *data);
void	ft_free(char **tab);
void	ft_exec_cleanup(t_struct *data, t_args *arg, int cmd_count);
void	ft_free_one_arg(t_args *arg);
void	ft_free_args(char ***args);

// CLEAR TO FUNCTION	

int		ft_isalnum(int c);
char	*ft_replace(char *tab, int i);
char	**ft_clear(char **tab, int i, int dquote, int quote);
char	**ft_clear_to_function(char **tab);

// ECHO //

int		ft_is_good_flag(char *s);
int		ft_is_wrong_flag(char *s);
int		ft_count_good_flags(char **tab);
int		ft_echo(char **args);
int		ft_echo_pipe(t_struct *data, t_args *arg, char **args, char **paths);

// PWD //

int		ft_pwd(char **args);
int		ft_pwd_pipe(t_struct *data, t_args *arg, char **args, char **path);

// CD //

char	*ft_remove_home(char *s1);
char	*ft_get_home(t_struct *data);
int		ft_cd_main(t_struct *data, char **args, int i, char *path);
int		ft_cd(t_struct *data, char **args);
int		ft_cd_pipe(t_struct *data, t_args *arg, char **args, char **path);

// ENV //

int		ft_env_pipe(t_struct *data, t_args *arg, char **args, char **path);
int		ft_env(t_struct *data);

// EXIT //

int		ft_exit(t_struct *data, t_args *arg, char **args, char **path);
int		ft_exit_pipe(t_struct *data, t_args *arg, char **args, char **path);

// UNSET //

char	*ft_str_with_equal(char *args);
int		ft_unset(t_struct *data, char **args);
int		ft_unset_pipe(t_struct *data, t_args *arg, char **args, char **path);

// EXPORT //

void	ft_export_printf_ordered(t_struct *data);
int		ft_export(t_struct *data, char **args);
int		ft_export_pipe(t_struct *data, t_args *arg, char **args, char **path);

// EXPORT UTILIS //

char	*ft_str_until_equal(char *args);
int		ft_search(char *str, char **tab);
void	ft_export_add(t_struct *data, char *args);
void	ft_export_update(t_struct *data, char *args);

// HISTORY //

void	ft_putchar_fd(char c, int fd);
void	ft_update_history(char *line);
void 	ft_set_up_history(void);

// HISTORY UTILIS //

int		ft_read_line(int fd, char **stock);
char	*get_next_line(int fd);
char	*ft_to_keep(char *string);
char	*ft_to_return(char *string);

// TOOLS //

void	ft_swap(char *s1, char *s2);
int		ft_strcmp(char *s1, char *s2);
char	**ft_replace_tab(char **tab, char **new_tab, char *new);
int		ft_strchr_gnl(const char *s, int c);
char	*ft_strjoin_gnl(char *s1, char *s2);

#endif