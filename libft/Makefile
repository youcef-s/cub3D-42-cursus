NAME = libft.a

RM = rm -rf

AR = ar rcs

SRC =	ft_strnstr.c\
		ft_strncmp.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_atoi.c\
		ft_memset.c\
		ft_bzero.c\
		ft_strdup.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_strlen.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_strchr.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_isprint.c\
		ft_strrchr.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_calloc.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_itoa.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_strmapi.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_split.c

BONUS_SRC = ft_lstnew.c\
			ft_lstadd_front.c\
			ft_lstsize.c\
			ft_lstlast.c\
			ft_lstadd_back.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstiter.c\
			ft_lstmap.c

OBJECTS = $(SRC:.c=.o)

BONUS_OBJS = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(AR) $(NAME) $(OBJECTS)

.c.o: $(SRC) $(BONUS_SRC) $(HDR)
	@cc -c $< -o $(<:.c=.o)
	@echo "Just a few more seconds"

bonus: $(BONUS_OBJS) $(OBJECTS)
	@$(AR) $(NAME) $(OBJECTS) $(BONUS_OBJS)

clean:
	@$(RM) $(OBJECTS) $(BONUS_OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re