SRC = ./src/main_cub3d.c  ./src/parsing/inspect.c ./src/parsing/start_parsing.c ./src/parsing/store.c \
	./src/f_tools/drawing_tools_1.c ./src/f_tools/drawing_tools_2.c ./src/f_tools/gnl.c \
	./src/f_tools/general_tools_1.c ./src/f_tools/general_tools_2.c ./src/f_tools/general_tools_3.c \
	./src/f_tools/parsing_tools_1.c ./src/f_tools/parsing_tools_2.c \
	./src/f_tools/exec_tools_1.c \
	./src/f_tools/exec_tools_2.c \
	./src/f_tools/raycasting_tools.c \
	./exec/drawing.c ./exec/ft_3d.c ./exec/raycasting.c \
	./exec/send_ray.c ./exec/start_exec.c ./exec/keys_handler.c\
	./exec/f_keys_handler.c

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
	clear && ./$(NAME) ./maps/map1.cub

re: fclean all