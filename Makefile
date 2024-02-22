NAME = so_long

CC = cc

CFLAGS = -Wall -Wextra -Werror 

INCLUDES = -I/opt/X11/include -Imlx

RM = rm -f

SRC = so_long.c ft_putdec.c ft_split.c get_next_line.c get_next_line_utils.c \
	  ft_putchar.c ft_putstr.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)

%.o: %.c so_long.h
		 $(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
		$(RM) $(OBJ) 

fclean: clean
		$(RM) $(NAME)

re: fclean all
