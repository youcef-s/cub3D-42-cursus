NAME = cub3D

GNL = gnl/get_next_line.c gnl/get_next_line_utils.c

PARSING_SRC = $(addprefix parsing/, check_elements.c check_walls.c parsing.c fill_something.c ft_split2.c)

RENDERING_SRC = $(addprefix rendering/, init.c start_mlx.c hooks.c update.c move.c ray_init.c utils.c)

SRC = cub3d.c $(RENDERING_SRC) $(GNL) $(PARSING_SRC)

HDR = cub3d.h libft/libft.h gnl/get_next_line.h

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@gcc -lmlx -framework OpenGL -framework AppKit $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "\033[0;32mIt's time to play a game\033[0;37m"

.c.o: $(SRC) $(LIBFT) $(HDR)
	@cc $(CFLAGS) -Imlx -c $< -o $(<:.c=.o)
	@echo "Just a few more seconds"

$(LIBFT):
	@make bonus -C libft/

clean:
	@rm -f $(OBJ)
	@make clean -C libft/
	@echo "Object files have been removed"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft/
	@echo "It's all clean"

re: fclean all
