NAME = cube3D

GNL = gnl/get_next_line.c gnl/get_next_line_utils.c

SRC = cub3d.c check_elements.c check_walls.c parsing.c fill_something.c $(GNL)

HDR = cub3d.h libft/libft.h gnl/get_next_line.h

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(HDR)
	@cc $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "It's time to play a game"

.c.o: $(SRC) $(LIBFT) $(HDR)
	@cc $(CFLAGS) -c $< -o $(<:.c=.o)
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