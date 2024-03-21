NAME = so_long

CC = cc

CFLAGS = -Wall -Wextra -Werror -Imlx

RM = rm -f

SRC = so_long.c ft_putdec.c ft_split.c get_next_line.c get_next_line_utils.c \
	  ft_putchar.c ft_putstr.c move_player.c so_long_utilis.c check_map.c ft_strcmp.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c so_long.h
		 $(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJ) 

fclean: clean
		$(RM) $(NAME)

re: fclean all
