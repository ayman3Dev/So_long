#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include "so_long.h"
#include <stdio.h>

typedef struct s_all{
	void *player_img;
	void *route_img;
	void *wall_img;
	void *exit_img;
	void *coin_img;
	void *mlx;
	void *win;
	char *allmap;
	char **spli_allmap;
}t_all;

typedef struct s_size{
	int height;
	int width;
	int player_x;
	int player_y;
	int compte_total;
	int player;
	int coin ;
	int door;
}t_size;

void	move_player(int direction, t_all *all, t_size *size)
{
	int	x;
	int	y;
	size->compte_total = 0;
	x = 0;
	y = 0;
	while (y < size->height)
	{
		x = 0;
		while (x < size->width)
		{
			if (all->spli_allmap[y][x] == 'P')
			{
				size->player_y = y;
				size->player_x = x;
				break ;
			}
			x++;
		}
		if (all->spli_allmap[y][x] == 'P')
			break ;
		y++;
	}

	x = size->player_x;
	y = size->player_y;

	if (direction == 0)
	{
		if (size->player_y > 0 && all->spli_allmap[size->player_y -  1][size->player_x] !=
		'1' && !(all->spli_allmap[size->player_y - 1][size->player_x] == 'E' && size->coin > 0))
		{
			size->player_y--;
			ft_putdec(++size->compte_total);
			ft_putchar('\n');	
		}
	}
	else if (direction == 1)
	{
		if (size->player_y < size->height - 1 &&
			all->spli_allmap[size->player_y + 1][size->player_x] != '1' &&
			!(all->spli_allmap[size->player_y + 1][size->player_x] == 'E' && size->coin > 0)) 
		{
			size->player_y++;
			ft_putdec(++size->compte_total);
			ft_putchar('\n');
		}
	}
	else if (direction == 2)
	{
		if (size->player_x > 0 && all->spli_allmap[size->player_y][size->player_x - 1] != '1'
		&& !(all->spli_allmap[size->player_y][size->player_x - 1] == 'E' && size->coin > 0))
		{
			size->player_x--;
			ft_putdec(++size->compte_total);
			ft_putchar('\n');
		}
	}
	else if (direction == 3)
	{
		if (size->player_x < size->width- 1 &&
			all->spli_allmap[size->player_y][size->player_x + 1] != '1' &&
			!(all->spli_allmap[size->player_y][size->player_x + 1] == 'E' && size->coin > 0))
		{
			size->player_x++;
			ft_putdec(++size->compte_total);
			ft_putchar('\n');
		}
	}
	if (all->spli_allmap[size->player_y][size->player_x] == 'E' && size->coin <= 0)
	{
		mlx_put_image_to_window(all->mlx, all->win, all->route_img, x * 50, y * 50);
		mlx_put_image_to_window(all->mlx, all->win, all->exit_img, all->player_x * 50, size->player_y * 50);
		exit(0);
	}
	else
	{
		if (spli_allmap[size->player_y][size->player_x] == 'C')
			size->coin--;
		mlx_put_image_to_window(all.mlx, all.win, all.route_img, x * 50, y * 50);
		mlx_put_image_to_window(all.mlx, all.win, all.player_img, size->player_x * 50, size->player_y * 50);
	}
}

char *ft_get_allmap(char *argv_one, int fd)
{
	char *allmap = NULL;
	char *temp = NULL;

	argv_one = get_next_line(fd);
	while (argv_one)
	{
		temp = allmap;
		allmap = ft_strjoin(allmap, argv_one);
		free(argv_one);
		free(temp);
		argv_one = get_next_line(fd);
	}
	close (fd);
	return (allmap);
}

int ft_check(char *allmap, t_size *size)
{
	int i;
	
	i = 0;
	while (allmap[i] != '\0')
	{
		if ((allmap[i] == '\n' && allmap[i + 1] == '\n') || allmap[0] != '1')
			return (printf("error", NULL));
		if (allmap[i] != 'P' && allmap[i] != 'E' && allmap[i] != 'C'
			&& allmap[i] != '\n' && allmap[i] != '0' && allmap[i] != '1')
			return (printf("error",NULL));
		if (allmap[i] == 'P')
			size->player++;
		if (allmap[i] == 'C')
			size->coin++;
		if (allmap[i] == 'E')
			size->door++;
		i++;
	}
	if (size->player != 1 || size->coin < 1 || size->door != 1 || allmap[--i] != '1')
		return (printf("error", NULL));
	return 0;
}

int ft_check_lenght(char *allmap)
{
	int i = 0;
	int j = 0;
	int temp_width = 0;
	int width_map = 0;
	while (allmap[i] != '\0')
	{
		if (allmap[i] == '\n' || allmap[i] == '\0')
		{
			temp_width = i - j + 1;
			j = i + 1;
		}
		if (width_map == 0)
			width_map = temp_width;
		else if (width_map != temp_width)
			return (write(1, "Error\n", 6), 1);
		i++;
	}
	return (0);
}
char **ft_checkmap(t_all *all)
{
	char **spli_allmap;
	int i;
	int y;
	t_size size;
	size.height = 0;
	size.width = 0;
	i = 0;
	if (ft_check(all->allmap) != 0 || ft_check_lenght(all->allmap))
		exit(1);
	spli_allmap = ft_split(all->allmap, '\n');
	size.width = strlen(spli_allmap[0]);
	while (spli_allmap[size.height] != NULL)
		size.height++;
	i = 0;
	while (spli_allmap[0][i] != '\0' && spli_allmap[size.height - 1][i] != '\0')
	{ 
		if (spli_allmap[0][i] != '1' || spli_allmap[size.height - 1][i] != '1')
		{
			printf("error map");
			return (NULL);
		}
		i++;
	}
	y = 0;
	i = 0;
	while (y < size.height)
	{
		if (spli_allmap[y][0] != '1' || spli_allmap[y][size.width - 1] != '1')
		{
			write (1, "ERROR2", 6);
			return (NULL);
		}
		y++;
	}
	return (spli_allmap);
}


int	key_handle(int key, t_all *all, t_size *size)
{
	if (key == 13) 
		move_player(0, &all, &size);
	else if (key == 1)
		move_player(1, &all, &size);
	else if (key == 0)
		move_player(2, &all, &size);
	else if (key == 2)
		move_player(3, &all, &size);
	else if (key == 53)
	{
		write (1, "EXIT", 4);
		exit(0);
	}
	return (0);
}

void ft_affich_imgs(t_all *all)
{
	int width_map = 0;
	int height_map = 0;
	int width = 0;
	int height = 0;
	// char *allmap = NULL;
	void *win;
	width_map = strlen(all->spli_allmap[0]);
	while (all->spli_allmap[height_map] != NULL)
		height_map++;
	all->win = mlx_new_window(all->mlx, width_map * 50, height_map * 50, "so_long");
	all->player_img = mlx_xpm_file_to_image(all->mlx, "Graphic/player.xpm", &width, &height);
	all->route_img = mlx_xpm_file_to_image(all->mlx, "Graphic/texturee.xpm", &width, &height);
	all->wall_img = mlx_xpm_file_to_image(all->mlx, "Graphic/wall1708384213.xpm", &width, &height);
	all->exit_img = mlx_xpm_file_to_image(all->mlx, "Graphic/Door.xpm", &width, &height);
	all->coin_img = mlx_xpm_file_to_image(all->mlx, "Graphic/coin.xpm", &width, &height);
	int x = 0;
	int y = 0;
	while (spli_allmap[y] != NULL)
	{
		x = 0;
		while (all->spli_allmap[y][x] != '\0')
		{
			if (all->spli_allmap[y][x] == '0')
				mlx_put_image_to_window(all->mlx, all->win, all->route_img, x * 50, y * 50);
			else if(all->spli_allmap[y][x] == '1')
				mlx_put_image_to_window(all->mlx, all->win, all->wall_img, x * 50, y * 50);
			else if (all->spli_allmap[y][x] == 'P')
				mlx_put_image_to_window(all->mlx, all->win, all->player_img, x * 50, y * 50);
			else if (all->spli_allmap[y][x] == 'E')
				mlx_put_image_to_window(all->mlx, all->win, all->exit_img, x * 50, y * 50);
			else if (all->spli_allmap[y][x] == 'C')
				mlx_put_image_to_window(all->mlx, all->win, all->coin_img, x * 50, y * 50);
			x++;
		}
		y++;
	}
	mlx_key_hook(all->win, key_handle, all->mlx);
}
int main (int argc, char **argv)
{
	int fd = 0;
	t_all all;

	if (argc != 2)
		return (1);
	
	fd = open (argv[1], O_RDWR);
	all.mlx = mlx_init();
	if (!all.mlx)
		exit(1);
	all.allmap = ft_get_allmap(argv[1], fd);
	all.spli_allmap = ft_checkmap(all.allmap);
	ft_affich_imgs(&all);
	mlx_loop(all.mlx);
}