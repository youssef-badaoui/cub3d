# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/04 18:27:34 by Ma3ert            #+#    #+#              #
#    Updated: 2022/08/28 15:09:41 by ybadaoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = cub3d.c exec/casting.c exec/trigonometric.c exec/exec_tools.c utils/gnl.c\
	parse/parsing_tools.c parse/parsing.c exec/send_ray.c exec/drawing.c \
	utils/utils.c

OBJ = $(SRC:.c=.o)

NAME = cub3d

HEADERS = ./headers/cub3d.h ./headers/struct.h

CC = gcc

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(FLAGS) $(MLX_FLAGS) $(OBJ) -o $(NAME)

%.o : %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

hoho: all clean
	clear && ./$(NAME) maps/Smap.cub

re: fclean all