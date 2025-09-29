# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 16:26:27 by pfreire-          #+#    #+#              #
#    Updated: 2025/09/29 12:04:21 by pfreire-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = libft.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
INCS    = -I.

SRC := $(shell find . -type f -name "*.c" ! -name "main.c")
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
