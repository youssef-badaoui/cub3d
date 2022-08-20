# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/04 18:27:34 by Ma3ert            #+#    #+#              #
#    Updated: 2022/08/19 19:01:49 by Ma3ert           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = cub3d.c exec/casting.c exec/trigonometric.c exec/exec_tools.c utils/gnl.c\
	utils/parsing_tools.c utils/utils.c

OBJ = $(SRC:.c=.o)

NAME = cub3d

HEADERS = ./headers/cub3d.h

CC = gcc

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(FLAGS) $(MLX_FLAGS) $(OBJ) -o $(NAME)

%.o : %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

hoho: all clean
	clear && ./$(NAME) maps/smap.cub

re: fclean all