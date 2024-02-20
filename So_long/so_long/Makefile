NAME = so_long.a

CC = cc

CFLAGS = -Wall -Wextra -Werror



RM = rm -f

SRC = so_long

INCLUDES = -I/opt/X11/include -Imlx

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
