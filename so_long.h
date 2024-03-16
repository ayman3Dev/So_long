/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:05:22 by aaaraba           #+#    #+#             */
/*   Updated: 2024/03/15 02:34:42 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h> 
# include <unistd.h> 
# include <fcntl.h>
# include <mlx.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif

typedef struct s_size
{
	int	height;
	int	width;
	int	p_x;
	int	p_y;
	int	player;
	int	coin;
	int	coin_check;
	int	door;
	int	x;
	int	y;
}	t_size;

typedef struct s_all
{
	void	*p_img;
	void	*r_img;
	void	*wall_img;
	void	*exit_img;
	void	*coin_img;
	void	*mlx;
	void	*win;
	char	*allmap;
	char	**map_2d;
	char	**map_2d_copy;
	int		compte_total;
	int		i;
	int		j;
	int		fd;
	t_size	size;
}	t_all;

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(char const *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
int		ft_putchar(int c);
int		ft_putdec(int n);
int		ft_putstr(char *s);
char	**ft_split(char const *s, char c);
void	move_player_down(t_all *all, t_size *size);
void	move_player_up(t_all *all, t_size *size);
void	move_player_right(t_all *all, t_size *size);
void	move_player_left(t_all *all, t_size *size);
void	ft_position(t_all *all);
void	ft_change_imgs(t_all *all, t_size *size);
char	*ft_get_allmap(char *argv_one, t_all *all);
int		ft_check(char *allmap, t_size *size);
int		ft_check_lenght(char *allmap);
char	**ft_checkmap(t_all *all);
int		ft_init(t_all *all);
int		ft_check_access(t_all *all, int x, int y);
int		ft_cheak_map_char(t_all *all);
void	ft_free(char **array);
void	ft_free_all(t_all *all);
int		ft_exit(t_all *all);

#endif