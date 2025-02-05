/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:53:12 by tfauve-p          #+#    #+#             */
/*   Updated: 2025/01/09 11:28:14 by gprunet          ###   ########.fr       */
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
	int		*redir;
	int		nb_redir;
	char	**tmp_arg;
	char	*line;
	char	**tab;
	char	**path;
	char	*path_to_home;
	int		pipefd[2];
	int		in_fd;
	int		out_fd;
	char	**env;
	int		launched_env;
	int		saved_stdout;
	int		saved_stdin;
	int		input;
	int		output;
	int		n_in;
	int		n_out;
	int		heredoc;
	int		n_heredoc;
	int		status;
	int		i;
	int		count_redir;
	int		temp_fd;
	int		last;
	int		total;
	int		stop;
	pid_t	pid;
}	t_struct;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	**input;
	char	**output;
	char	*delimiter;
	int		pos_redir;
	int		c_in;
	int		c_out;
	int		m_in;
	int		m_out;
	int		stop;
	int		append;
	int		put;
	int		b_input;
	int		b_output;
}	t_args;

extern volatile sig_atomic_t	g_sig_receiver;

// SIGNALS //

// MAIN //

void	ft_main(t_struct *data);

// PARSER //

void	ft_printf_parsing(char **tab);
int		ft_parser(t_struct *data);

// PARSER UTILIS //

void	ft_error_parsing(void);
int		ft_nb_arg(char **tab);
int		ft_check_starting_pipe(t_struct *data);
int		ft_check_semicolon(t_struct *data);
int		ft_check_backslash(t_struct *data);

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

char	**ft_write_starting_env(char **tab);
void	ft_write_env(t_struct *data);
void	ft_set_up_env(t_struct *data, char **environ);

// SIGNALS //

void	ft_init_signals(void);
void	ft_get_signal_int(int sig);
void	ft_get_signal_quit(int sig);
void	ft_handle_signals(void);

// EXEC //

void	ft_exec(t_struct *data);
void	ft_algo_exec(t_struct *data, t_args **arg, int i, int cmd_count);
void	ft_pipe_exec(t_struct *data, char **args, char **path, t_args **arg);
int		split_args(char **arg, t_args **new_args, t_struct *data);

// REDIR CMD //

int		redir_cmd(t_args *arg, t_struct *data);
int		handle_redirection(t_args *arg, t_struct *data);

// FT EXEC UTILIS //

char	**ft_fill_args(char *cmds, char **args);
void	ft_exec_init(t_struct *data, t_args **arg);
void	final_reset(t_struct *data);
int		pipe_check(t_struct *data, int i, int cmd_count, char *delimiter);
void	reset_pipe_exit(t_struct *data, int i, int cmd_count, t_args *arg);

// FT EXEC UTILIS 2 //

int		doc_count(char *f, char c, t_struct *data);
void	init_puts(t_args *args);
void	update_puts(t_args *arg, t_struct *data);
int		c_puts(char **temp, char c, t_struct *data);
int		get_max(char **temp, char c, int current, t_struct *data);

// ALGO EXEC UTILIS //

int		algo_heredoc(t_struct *data, t_args **arg, int i, int cmd_count);
int		algo_built(t_struct *data, char **args, char **true_path, t_args **arg);
void	algo_fork(t_struct *data, char **args, char **true_path, t_args **arg);
void	post_algo_free(char **args, char **true_path);
void	reset_stds(t_struct *data, t_args *arg, int i, int cmd_count);

// EXEC UTILIS //

char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
int		ft_strchr(char *s, char c);
int		is_empty(char *arg);
int		is_flag(char *arg);

//EXEC UTILIS 2 //

void	ft_free_child(char **args, t_struct *data, t_args **arg, char **path);
char	**ft_assign_path(t_struct *data, char *cmd);
char	**check_access(char *tmp, int s);
int		ft_hard_path(char *arg);
char	**ft_true_path(t_struct *data, char *cmd);

// EXEC UTILIS 3 //

char	**ft_split_cleared(char *s, char c);
int		ft_function_pipe(t_struct *d, char **args, char **path, t_args **arg);
int		ft_check_function(t_struct *d, char **args, char **path, t_args **arg);
int		ft_strncmp(char *s1, char *s2, int n);

// CHECK BUILTINS //

int		ft_check_builtins(char *cmd, t_args *arg);
int		ft_check_builtins_init(char *arg);

// SPLIT ARGS UTILIS //

int		c_args(char **temp);
t_args	ft_assign_args(t_args *new_args, char **temp, t_struct *data);
char	*ft_strstr(char *str, char *find);
int		ft_check_hard_path(t_struct *data, char *arg);
int		ft_check_path(t_struct *data, char *arg);

// CHECK TEMP //

int		temp_check(char **temp, t_struct *data, int time);
int		single_check(char *temp, t_struct *data, int *r_nb, int *nb);
void	add_full(char *line, char **full);

// REDIR CMD UTILIS //

int		special_case(char *cmd, t_struct *data, char **args, t_args *arg);
int		check_fd(int fd, t_args *a);

// REDIR UTILIS //

int		q_redir(t_struct *data, char *temp, t_args *args, int i);

// REDIRECTION //

int		check_redirection(char **temp, t_args *new_args, int *i, int *j);
int		separate_command(char **temp, t_args *new_args, int *i, int *args);
int		separate_command2(char **temp, t_args *new_args, int *i);
char	*check_n(char **temp, int *i, char *c, t_args *args);

// REDIRECTION UTILIS //

int		check_redirection_cmd(char *arg);
char	*ft_strstr(char *str, char *find);
int		check_append(char *temp);
void	command2_utilis(char **temp, t_args *new_args, int *i, int j);
void	command1_utilis(char **temp, t_args *new_args, int *i, int j);

// GET COMMAND //

int		get_cmd(char **temp, int *i, t_args *args);
char	*get_cmd_output(char *temp);
int		sort_redir(char *temp, t_args *new_args, char c, int com);
void	else_command(t_args *args, char **temp, int *i);

// ASSIGN ARGS UTILIS //

int		check_built(char *temp, t_args *new_args, int *i, int len);
int		check_string(char *temp, int *i);
int		verif_command(t_struct *data, char **cmd, t_args *new_args);
int		ft_check_cmd(t_args *new_args, int i, char *str);
int		ft_tablen(char **tab);

// COUNT COMMANDS //

void	print_error(t_struct *data, char *cmd);
int		get_count(t_args *arg, int cmd_count, t_struct *data);
int		count_commands(char **arg);
int		check_pos(char *temp, char c, t_args *args);

// FREE //

void	ft_free_struct(t_args **arg, int cmd_count);
void	ft_free_all(t_struct *data);
void	ft_final_free(t_struct *data);
void	ft_free(char **tab);
void	ft_exec_cleanup(t_struct *data, t_args *arg, int cmd_count);

// CLEAR TO FUNCTION	

int		ft_isalnum(int c);
char	*ft_replace(char *tab, int i);
char	**ft_clear(char **tab, int i, int dquote, int quote);
char	**ft_clear_to_function(char **tab);

//	HEREDOC //

int		ft_heredoc(t_args *arg, t_struct *data);
int		ft_heredoc_pipe(t_args *arg, t_struct *data, char **args, char **path);
int		heredoc_algo(int pipefd, t_args *arg, t_struct *data);
int		check_heredoc(char **temp, t_args *new_args, int *i);
char	*assign_delimiter(char *temp, t_args *new_args);

// ECHO //

int		ft_is_first_n_flag(char *tab);
int		ft_echo(char **args);
int		ft_echo_pipe(t_struct *data, t_args **arg, char **args, char **paths);

// PWD //

int		ft_pwd(char **args);
int		ft_pwd_pipe(t_struct *data, t_args **arg, char **args, char **path);

// CD //

char	*ft_remove_home(char *s1);
char	*ft_get_home(t_struct *data);
int		ft_cd_main(t_struct *data, char **args, int i, char *path);
int		ft_cd(t_struct *data, char **args);
int		ft_cd_pipe(t_struct *data, t_args **arg, char **args, char **path);

// CD UTILIS //

int		ft_straight_home(t_struct *data);
void	ft_set_up_home(t_struct *data);

// ENV //

int		ft_env_pipe(t_struct *data, t_args **arg, char **args, char **path);
int		ft_env(t_struct *data);

// EXIT //

int		ft_bf_exit(t_struct *data, t_args **arg, char **args, char **path);
int		ft_exit(t_struct *data, t_args **arg, char **args, char **path);
int		ft_exit_pipe(t_struct *data, t_args **arg, char **args, char **path);

// UNSET //

char	*ft_str_with_equal(char *args);
void	ft_delete_tab_case(t_struct *data, int i, int a, int b);
int		ft_unset_main(t_struct *data, char *str);
int		ft_unset(t_struct *data, char **args);
int		ft_unset_pipe(t_struct *data, t_args **arg, char **args, char **path);

// EXPORT //

int		ft_ok_1(char *args);
int		ft_ok_2(char *args);
void	ft_export_printf_ordered(t_struct *data);
int		ft_export(t_struct *data, char **args);
int		ft_export_pipe(t_struct *data, t_args **arg, char **args, char **path);

// EXPORT UTILIS //

char	*ft_put_string_to_tab(t_struct *data, char **tab, int i, int j);
char	*ft_str_until_equal(char *args);
int		ft_search(char *str, char **tab);
void	ft_export_add(t_struct *data, char *args);
int		ft_ok_3(char *args);

// EXPAND //

char	**ft_expand_join(char **tab, int j);
char	*ft_get_from_env(t_struct *data, char *s);
char	*ft_expanded(t_struct *data, char *s);
char	**ft_expand_replace(t_struct *data, char **tab);
void	ft_expand(t_struct *data);

// EXPAND UTILIS //

char	*ft_copy_tab(char *s);
int		ft_countword_expand(char const *s, char c);
char	**ft_mecanism_expand(int length, char **tab, char *line, char c);
char	**ft_split_expand(char *s, char c);

// HISTORY //

void	ft_putchar_fd(char c, int fd);
void	ft_update_history(char *line);
void	ft_set_up_history(void);

// HISTORY UTILIS //

int		ft_read_line(int fd, char **stock);
char	*get_next_line(int fd);
char	*ft_to_keep(char *string);
char	*ft_to_return(char *string);

// TOOLS //

char	**ft_swap(t_struct *data, int i, int j);
int		ft_strcmp(char *s1, char *s2);
char	**ft_replace_tab(char **tab, char **new_tab, char *new);
int		ft_strchr_gnl(const char *s, int c);
char	*ft_strjoin_gnl(char *s1, char *s2);

// TOOLS 2 //

int		ft_unset_export(t_struct *data, char **args);
int		ft_export_add_or_update(t_struct *data, char **args, int i);
int		ft_search_expand(char *str, char **tab);
int		ft_isalpha(int c);
int		ft_write_error(char *c);

// TOOLS 3 // 

void	ft_set_up_data_path(t_struct *data);
void	heredoc_exit(t_struct *data);
void	ft_free_child2(char **args, t_struct *data, char **path);
int		ft_strncmp(char *s1, char *s2, int n);

// RETURN STATUS //

void	ft_export_update(t_struct *data, char *args);
int		ft_negative(int n);
int		ft_dizaine(long nombre);
char	*ft_itoa(int n);
int		ft_update_return_status(t_struct *data, int i);

#endif