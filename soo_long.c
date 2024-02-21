#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <string.h>
#include "libft/libft.h"


char **mab_spli;
int y = 0;
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
int coin_i = 0;

static int	ft_countword(char const *s, char c)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			size++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (size);
}

static void	ft_free(char **array, int i)
{
	while (i)
	{
		free(array[--i]);
	}
	free(array);
}

static char	*allocate_string(const char *s, int start, int end)
{
	char	*array;
	int		i;

	i = 0;
	array = (char *)malloc(sizeof(char) * (end - start + 1));
	if (array == NULL)
		return (NULL);
	while (start < end && s[start])
	{
		array[i] = s[start];
		start++;
		i++;
	}
	array[start] = 0;
	return (array);
}

static int	len_worlds(char const *s, char c)
{
	int	j;

	j = 0;
	while (s[j] && s[j] != c)
		j++;
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		size;
	int		i;

	if (s == NULL) 
		return (NULL);
	size = ft_countword(s, c);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	if (array == NULL)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		while (*s && *s == c)
			s++;
		array[i] = allocate_string(s, 0, len_worlds(s, c));
		if (array[i] == NULL)
		{
			ft_free(array, i);
			return (0);
		}
		s = s + len_worlds(s, c);
	}
	array[i] = NULL;
	return (array);
}

void move_player(int direction, int width_map, int height_map, char **map_split)
{
    int old_x = player_x;
    int old_y = player_y;

    if (direction ==  0)
	{  //lfo9
        if (player_y >  0 && map_split[player_y -  1][player_x] != '1' && !(map_split[player_y - 1][player_x] == 'E' && coin_i > 0))
		{
            player_y--;
        }
    }
	else  if (direction ==  1)
	{  //lte7t
        if (player_y < height_map -  1 && map_split[player_y +  1][player_x] != '1' && !(map_split[player_y + 1][player_x] == 'E' && coin_i > 0)) {
            player_y++;
        }
    }
	else if (direction ==  2)
	{  //lisser
        if (player_x >  0 && map_split[player_y][player_x -  1] != '1' && !(map_split[player_y][player_x - 1] == 'E' && coin_i > 0))
		{
            player_x--;
        }
    }
	else if (direction ==  3)
	{  //limmen
        if (player_x < width_map -  1 && map_split[player_y][player_x +  1] != '1' && !(map_split[player_y][player_x + 1] == 'E' && coin_i > 0)) {
            player_x++;
        }
    }
	if (map_split[player_y][player_x] == 'E' && coin_i <= 0)
	{
    	mlx_put_image_to_window(mlx, win, route_img, old_x *  50, old_y *  50); // Erase the player from the old position
    	mlx_put_image_to_window(mlx, win, exit_img, player_x *  50, player_y *  50);
		exit(0); // Draw the player at the new position
	}
	else
	{
		if (map_split[player_y][player_x] == 'C')
			coin_i--;
		printf("%d\n", coin_i);
		map_split[player_y][player_x] = '0';
		mlx_put_image_to_window(mlx, win, route_img, old_x *  50, old_y *  50); // Erase the player from the old position
    	mlx_put_image_to_window(mlx, win, player_img, player_x *  50, player_y *  50); 

	}
    // Redraw the map and the player
}

//chat
int key_handle(int key)
{
    int w = 13;
    int s = 1;
    int a = 0;
    int d = 2;

    // Call the move_player function with the appropriate parameters
    if (key == w) {
        move_player(0, width_map, height_map, mab_spli);
    } else if (key == s) {
        move_player(1, width_map, height_map, mab_spli);
    } else if (key == a) {
        move_player(2, width_map, height_map, mab_spli);
    } else if (key == d) {
        move_player(3, width_map, height_map, mab_spli);
    } else if (key == 53) {
        exit(0);
    }

    return (0);
}


int main (void)
{
	int fd = open ("map.ber", O_RDWR);
	mlx = mlx_init();
	if (!mlx)
		return (1);
	allmap = get_next_line(fd);

	while (allmap)
	{
		temp = ft_strjoin(temp, allmap);
		allmap = get_next_line(fd);
	}
	int i = 0;
	int j = 0;

	while (temp[i] != '\0')
	{
		// printf("%c", temp[i]);
		if (temp[i] == '\n' || temp[i] == '\0')
		{
			++height_map;
			temp_width = i - j + 1;
			j = i + 1;
		}
		if(width_map == 0)
			width_map = temp_width;
		else if (width_map != temp_width)
			return (write(1, "Error\n", 6), 1);
		i++;
	}
	if (temp[i - 1] == '\n') {
		write(1, "Error\n", 6);
        return 1;
    }
	width_map -= 1;
	
	mab_spli = ft_split(temp, '\n');
	while (y < height_map)
	{
		x = 0;
		while (x < width_map)
		{
			if (mab_spli[y][x] == 'P')
			{
				player_y = y;
				player_x = x;
				break;
			}
			x++;
		}
		if (mab_spli[y][x] == 'P')
				break;
		y++;
	}

	close(fd);
	allmap = NULL;
	fd = open ("map.ber", O_RDWR);
	win = mlx_new_window(mlx, width_map * 50, height_map * 50, "so_long");

	player_img = mlx_xpm_file_to_image(mlx, "so_long/Graphic/player.xpm", &width , &height);
	route_img = mlx_xpm_file_to_image(mlx, "so_long/Graphic/texturee.xpm", &width , &height);
	void *wall_img = mlx_xpm_file_to_image(mlx, "so_long/Graphic/wall1708384213.xpm", &width , &height);
	exit_img = mlx_xpm_file_to_image(mlx, "so_long/Graphic/Door.xpm", &width , &height);
	void *coin_img = mlx_xpm_file_to_image(mlx, "so_long/Graphic/coin.xpm", &width , &height);
	while (line_number < height_map)
	{
		
		allmap = get_next_line(fd);
		line_width= 0;
		while (allmap != NULL && line_width < width_map)
		{
			if(allmap[line_width] == '0')
				mlx_put_image_to_window(mlx, win, route_img, line_width * 50, line_number * 50);
			else if(allmap[line_width] == '1')
				mlx_put_image_to_window(mlx, win, wall_img, line_width * 50, line_number * 50);
			else if (allmap[line_width] == 'P')
				mlx_put_image_to_window(mlx, win, player_img, line_width * 50, line_number * 50);
			else if (allmap[line_width] == 'E')
				mlx_put_image_to_window(mlx, win, exit_img, line_width * 50, line_number * 50);
			else if (allmap[line_width] == 'C')
			{
				coin_i++;
				// printf("hello");
				mlx_put_image_to_window(mlx, win, coin_img, line_width * 50, line_number * 50);

			}
			line_width++;
		}
		line_number++;
		free(allmap);
		allmap = NULL;
	}

	mlx_key_hook(win, key_handle, mlx);
	mlx_loop(mlx);
}
