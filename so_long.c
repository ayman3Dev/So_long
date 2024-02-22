#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "so_long.h"

int		compte_total = 0;
char 	**mab_spli;
int	y = 0;
int x = 0;
int player_x = 0;
int player_y = 0;
int height = 0;
int width = 0;
	
char *allmap;
int line_width;
int line_number =  0;
void *mlx;
char *temp = NULL;
int height_map = 1;
int temp_width = 0;
int width_map = 0;
void *player_img;
void *route_img;
void *exit_img;
void *win;
void *wall_img;
void *coin_img;
int coin_i = 0;
int player_door = 0;

void	move_player(int direction, int width_map, int height_map, char **map_split)
{
	int	old_x;
	int	old_y;

	old_x = player_x;
	old_y = player_y;
	if (direction == 0)
	{
		if (player_y >  0 && map_split[player_y -  1][player_x] !=
		'1' && !(map_split[player_y - 1][player_x] == 'E' && coin_i > 0))
		{
			player_y--;
			compte_total++;
			ft_putdec(compte_total);
			ft_putchar('\n');
		}
	}
	else if (direction == 1)
	{
		if (player_y < height_map - 1 &&
			map_split[player_y + 1][player_x] != '1' &&
			!(map_split[player_y + 1][player_x] == 'E' && coin_i > 0)) 
		{
			player_y++;
			compte_total++;
			ft_putdec(compte_total);
			ft_putchar('\n');
		}
	}
	else if (direction == 2)
	{
		if (player_x > 0 && map_split[player_y][player_x - 1] != '1'
		&& !(map_split[player_y][player_x - 1] == 'E' && coin_i > 0))
		{
			player_x--;
			compte_total++;
			ft_putdec(compte_total);
			ft_putchar('\n');
		}
	}
	else if (direction == 3)
	{
		if (player_x < width_map - 1 &&
			map_split[player_y][player_x + 1] != '1' &&
			!(map_split[player_y][player_x + 1] == 'E' && coin_i > 0))
		{
			player_x++;
			compte_total++;
			ft_putdec(compte_total);
			ft_putchar('\n');
		}
	}
	if (map_split[player_y][player_x] == 'E' && coin_i <= 0)
	{
		mlx_put_image_to_window(mlx, win, route_img, old_x * 50, old_y * 50);
		mlx_put_image_to_window(mlx, win, exit_img, player_x * 50, player_y * 50);
		exit(0);
	}
	else
	{
		if (map_split[player_y][player_x] == 'C')
			coin_i--;
		map_split[player_y][player_x] = '0';
		mlx_put_image_to_window(mlx, win, route_img, old_x * 50, old_y * 50);
		mlx_put_image_to_window(mlx, win, player_img, player_x * 50, player_y * 50);
	}
}

//chat
// int w = 13;
// int s = 1;
// int a = 0;
// int d = 2;

int	key_handle(int key)
{
	if (key == 13) 
		move_player(0, width_map, height_map, mab_spli);
	else if (key == 1)
		move_player(1, width_map, height_map, mab_spli);
	else if (key == 0)
		move_player(2, width_map, height_map, mab_spli);
	else if (key == 2)
		move_player(3, width_map, height_map, mab_spli);
	else if (key == 53)
		exit(0);
	return (0);
}

int	main(void)
{
	int	fd;
	int	i;
	int	j;

	fd = open ("map1.ber", O_RDWR);
	mlx = mlx_init();
	if (!mlx)
		return (1);
	allmap = get_next_line(fd);
	int check = 0;
	//function katchuf wach ster lewel fih chi character akher mn khir '1'
	while (allmap[check] != '\n')
	{
		if (allmap[check] != '1')
			{
				write(1, "Error\n", 6);
				return (1);
			}
		check++;
	}
	while (allmap)
	{
		temp = ft_strjoin(temp, allmap);
		allmap = get_next_line(fd);
	}
	i = 0;
	j = 0;
	while (temp[i] != '\0')
	{
		if (temp[i] == '\n' || temp[i] == '\0')
		{
			++height_map;
			temp_width = i - j + 1;
			j = i + 1;
		}
		if (width_map == 0)
			width_map = temp_width;
		else if (width_map != temp_width)
			return (write(1, "Error\n", 6), 1);
		i++;
	}
	if (temp[i - 1] == '\n')
	{
		write(1, "Error\n", 6);
		return (1);
	}
	width_map -= 1;
	mab_spli = ft_split(temp, '\n');
	printf("%d", width_map);
	printf("{%d}", height_map);
	while (y < height_map)
	{
		x = 0;
		while (x < width_map)
		{
			if (mab_spli[y][x] == 'P')
			{
				player_y = y;
				player_x = x;
				break ;
			}
			else if (mab_spli[y][0] != '1' || mab_spli[y][width_map - 1] != '1')
				{
					write (1, "ERROR", 5);
					return (1);
				}
			x++;
		}
		if (mab_spli[y][x] == 'P')
			break ;
		y++;
	}
	check = 0;
	while (mab_spli[height_map - 1][check] != '\0')
	{
		if (mab_spli[height_map - 1][check] != '1')
			{
				write(1, "Error\n", 6);
				return (1);
			}
		check++;
	}
	close(fd);
	allmap = NULL;
	fd = open ("map1.ber", O_RDWR);
	win = mlx_new_window(mlx, width_map * 50, height_map * 50, "so_long");
	player_img = mlx_xpm_file_to_image(mlx, "Graphic/player.xpm", &width, &height);
	route_img = mlx_xpm_file_to_image(mlx, "Graphic/texturee.xpm", &width, &height);
	wall_img = mlx_xpm_file_to_image(mlx, "Graphic/wall1708384213.xpm", &width, &height);
	exit_img = mlx_xpm_file_to_image(mlx, "Graphic/Door.xpm", &width, &height);
	coin_img = mlx_xpm_file_to_image(mlx, "Graphic/coin.xpm", &width, &height);
	while (line_number < height_map)
	{
		allmap = get_next_line(fd);

		line_width = 0;
		while (allmap && line_width < width_map)
		{
			if (allmap[line_width] == '0')
				mlx_put_image_to_window(mlx, win, route_img, line_width * 50, line_number * 50);
			else if(allmap[line_width] == '1')
				mlx_put_image_to_window(mlx, win, wall_img, line_width * 50, line_number * 50);
			else if (allmap[line_width] == 'P')
			{
				player_door++;
				mlx_put_image_to_window(mlx, win, player_img, line_width * 50, line_number * 50);
			}
			else if (allmap[line_width] == 'E')
			{
				player_door++;
				mlx_put_image_to_window(mlx, win, exit_img, line_width * 50, line_number * 50);
			}
			else if (allmap[line_width] == 'C')
			{
				coin_i++;
				mlx_put_image_to_window(mlx, win, coin_img, line_width * 50, line_number * 50);
			}
			line_width++;
		}
		if (player_door > 2)
			{
				write(1, "Error\n", 6);
				return (1);
			}
		line_number++;
		free(allmap);
		allmap = NULL;
	}
	mlx_key_hook(win, key_handle, mlx);
	mlx_loop(mlx);
}
