#ifndef LIBFT_H
# define LIBFT_H

#include <stdio.h> //delete it
#include <stdlib.h> 
#include <unistd.h> 
#include <fcntl.h>
#include <string.h> //delete it
# include <mlx.h>

//get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(char const *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
//get_next_line

//ft_printf
int		ft_putchar(int c);
int		ft_putdec(int n);
int		ft_putstr(char *s);
//ft_printf

char	**ft_split(char const *s, char c);

#endif