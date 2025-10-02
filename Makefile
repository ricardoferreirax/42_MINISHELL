# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 18:34:39 by rmedeiro          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2025/09/29 11:58:46 by pfreire-         ###   ########.fr        #
=======
#    Updated: 2025/10/01 16:29:53 by rmedeiro         ###   ########.fr        #
>>>>>>> ricardo
#                                                                              #
# **************************************************************************** #

NAME    = minishell

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g
INCS    = -Iinclude -Ilibft

LIBFT   = libft/libft.a

SRC_FILES = main.c \
			builtin/ft_cd.c \
			builtin/ft_echo.c \
			builtin/ft_pwd.c \
			builtin/ft_env.c \
			execution/builtin.c \
			execution/child_process.c \
			execution/cmd_path.c \
			execution/execute_cmds.c \
			execution/execution.c \
			execution/heredoc.c \
			execution/pipeline.c \
			execution/redirection.c \
			parsing/aux_funcs.c \
			parsing/fill_subcmd.c \
			parsing/init_fill_mini.c \
			parsing/parse.c \
			parsing/redir.c \
			parsing/split_ignore_quotes.c \
			parsing/utils.c \
			parsing/validate_input.c \
			utils/errors.c \
			utils/libft_utils.c \
			utils/pipe_utils.c \
			utils/split_quotes.c

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