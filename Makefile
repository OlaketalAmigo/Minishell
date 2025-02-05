# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 14:38:38 by tfauve-p          #+#    #+#              #
#    Updated: 2025/01/08 18:01:06 by gprunet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SOURCES_DIR = SOURCES/
INCLUDES_DIR = INCLUDES/
OBJECTS_DIR = OBJECTS/

SOURCES = \
	$(SOURCES_DIR)main.c \
	$(SOURCES_DIR)parser_checker.c \
	$(SOURCES_DIR)parser_split.c \
	$(SOURCES_DIR)parser_trim.c \
	$(SOURCES_DIR)parser_utilis.c \
	$(SOURCES_DIR)parser.c \
	$(SOURCES_DIR)signals.c \
	$(SOURCES_DIR)exec.c \
	$(SOURCES_DIR)ft_exec_utilis.c \
	$(SOURCES_DIR)ft_exec_utilis2.c \
	$(SOURCES_DIR)redir_cmd.c		\
	$(SOURCES_DIR)exec_utilis.c \
	$(SOURCES_DIR)exec_utilis2.c \
	$(SOURCES_DIR)exec_utilis3.c \
	$(SOURCES_DIR)free.c \
	$(SOURCES_DIR)echo.c \
	$(SOURCES_DIR)pwd.c \
	$(SOURCES_DIR)cd.c \
	$(SOURCES_DIR)cd_utilis.c \
	$(SOURCES_DIR)exit.c \
	$(SOURCES_DIR)env.c \
	$(SOURCES_DIR)unset.c \
	$(SOURCES_DIR)export.c \
	$(SOURCES_DIR)export_utilis.c \
	$(SOURCES_DIR)expand.c \
	$(SOURCES_DIR)expand_utilis.c \
	$(SOURCES_DIR)split_args_utilis.c \
	$(SOURCES_DIR)check_temp.c		\
	$(SOURCES_DIR)assign_args_utilis.c \
	$(SOURCES_DIR)set_up_env.c \
	$(SOURCES_DIR)history.c \
	$(SOURCES_DIR)history_utilis.c \
	$(SOURCES_DIR)tools.c \
	$(SOURCES_DIR)tools_2.c \
	$(SOURCES_DIR)tools_3.c \
	$(SOURCES_DIR)return_status.c	\
	$(SOURCES_DIR)algo_exec_utilis.c	\
	$(SOURCES_DIR)check_builtins.c	\
	$(SOURCES_DIR)redir_utilis.c	\
	$(SOURCES_DIR)redir_cmd_utilis.c	\
	$(SOURCES_DIR)redirection.c	\
	$(SOURCES_DIR)get_command.c	\
	$(SOURCES_DIR)redirection_utilis.c	\
	$(SOURCES_DIR)heredoc.c	\
	$(SOURCES_DIR)count_commands.c	\
	$(SOURCES_DIR)clear_to_function.c
	

OBJECTS = $(SOURCES:$(SOURCES_DIR)%.c=$(OBJECTS_DIR)%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

PURPLE = \033[0;35m
LIGHTPURPLE = \033[1;35m
RED = \033[0;31m
LIGHTRED = \033[1;31m
ORANGE = \033[0;33m
YELLOW = \033[1;33m
LIGHTGREEN = \033[1;32m
GREEN = \033[0;32m
LIGHTCYAN = \033[1;36m
CYAN = \033[0;36m
LIGHTBLUE = \033[1;34m
BLUE = \033[0;34m
RESET = \033[0;0m

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -lreadline -lcurses
	@clear

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJECTS_DIR)

fclean: clean
	@rm -f $(NAME)
	@clear

re: fclean all

.PHONY: all bonus clean fclean re

