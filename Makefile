NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Wextra -Werror 
RM = rm -f

SRC = ft_printf.c ft_putchar.c ft_puthexalow.c ft_putstr.c \
	  ft_printadd.c ft_putdec.c ft_puthexaupper.c ft_putudec.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

