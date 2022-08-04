# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/04 18:27:34 by Ma3ert            #+#    #+#              #
#    Updated: 2022/08/04 18:32:22 by Ma3ert           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = cub3d.c utils/gnl.c

OBJ = $(SRC:.c=.o)

NAME = cub3d

HEADERS = ./headers/cub3d.h

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all