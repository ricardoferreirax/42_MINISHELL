# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 18:34:39 by rmedeiro          #+#    #+#              #
#    Updated: 2025/09/29 11:58:46 by pfreire-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = minishell

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g
INCS    = -Iinclude -Ilibft

LIBFT   = libft/libft.a

SRC_FILES = \
	testing_main.c execution/execution.c execution/redirection.c \
	execution/pipeline.c execution/heredoc.c execution/builtin.c execution/cmd_path.c \
	execution/child_process.c execution/execute_cmds.c utils/errors.c utils/pipe_utils.c \
	utils/split_quotes.c builtin/ft_echo.c builtin/ft_pwd.c \
	parsing_test/parse.c parsing_test/pipeline_build.c parsing_test/redir_build.c \
	parsing_test/split_ignore_quotes.c parsing_test/subcmd_build.c parsing_test/validate_line.c \
	parsing_test/utils.c

OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -lreadline -lhistory -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -f $(OBJ_FILES)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

e: all clean

.PHONY: all clean fclean re