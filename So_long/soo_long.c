#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <string.h>
#include "libft/libft.h"



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

void move_player(int key, void *mlx, void *win, char **map, int player_x, int player_y) {
    int new_x = player_x;
    int new_y = player_y;

    // Determine the new position based on the key pressed
    if (key == 126 && map[player_y - 1][player_x] != '1') // Up arrow key
        new_y--;
    else if (key == 125 && map[player_y + 1][player_x] != '1') // Down arrow key
        new_y++;
    else if (key == 123 && map[player_y][player_x - 1] != '1') // Left arrow key
        new_x--;
    else if (key == 124 && map[player_y][player_x + 1] != '1') // Right arrow key
        new_x++;

    // Check if the new position is valid
    if (map[new_y][new_x] != '1') {
        // Erase the player from the current position
        mlx_put_image_to_window(mlx, win, route_img, player_x * 50, player_y * 50);
        
        // Update the player's position
        player_x = new_x;
        player_y = new_y;

        // Draw the player at the new position
        mlx_put_image_to_window(mlx, win, player_img, player_x * 50, player_y * 50);
    }
}


int key_handle(int key, void *ptr)
{

    if (key == 53)
    {
        printf("EXIT\n");
        exit(0);
    }
    return (0);
}

int main (int argc, char **argv)
{
	int y = 0;
	int x = 0;
	int height = 0;
	int width = 0;
	char *new;
	int c = 1;
	int fd = open ("map.ber", O_RDWR);
	char *allmap;
	int line_width;
	int line_number =  0;
	void *mlx = mlx_init();
	char *temp = NULL;
	if (!mlx)
		return (1);
	allmap = get_next_line(fd);
	int height_map = 1;
	int temp_width = 0;
	int width_map = 0;
	while (allmap)
	{
		temp = ft_strjoin(temp, allmap);
		allmap = get_next_line(fd);
	}
	int i = 0;
	int j = 0;

	while (temp[i] != '\0')
	{
		if (temp[i] == '\n' || temp[i] == '\0')
		{
			++height_map;
			temp_width = i - j + 1;
			j = i + 1;
		}
		if(width_map == 0)
			width_map = temp_width;
		else if (width_map != temp_width)
			return 1;
		i++;
	}
	if (temp[i - 1] == '\n') {
        return 1;
    }
	width_map -= 1;


	// allmap = get_next_line(fd);

	// int width_map = strlen(allmap) - 1;
	// // int height_map = 1;

	// // while (allmap)
	// // {
	// // 	allmap = get_next_line(fd);
	// // 	if(allmap == NULL)
	// // 		break;
	// // 	height_map++;
	// // }
	close(fd);
	allmap = NULL;
	fd = open ("map.ber", O_RDWR);
	void *win = mlx_new_window(mlx, width_map * 50, height_map * 50, "so_long");

	void *player_img = mlx_xpm_file_to_image(mlx, "so_long/Graphic/player.xpm", &width , &height);
	void *route_img = mlx_xpm_file_to_image(mlx, "so_long/Graphic/texturee.xpm", &width , &height);
	void *wall_img = mlx_xpm_file_to_image(mlx, "so_long/Graphic/wall1708384213.xpm", &width , &height);
	void *exit_img = mlx_xpm_file_to_image(mlx, "so_long/Graphic/Door.xpm", &width , &height);
	void *coin_img = mlx_xpm_file_to_image(mlx, "so_long/Graphic/coin.xpm", &width , &height);

	while (line_number < height_map * 50)
	{
		line_width= 0;
		allmap = get_next_line(fd);
		while (allmap && line_width < width_map * 50)
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
				mlx_put_image_to_window(mlx, win, coin_img, line_width * 50, line_number * 50);
			line_width++;
		}
		printf("Line %d: %s\n", line_number, allmap);
		line_number++;
		free(allmap);
		allmap = NULL;
	}
	mlx_key_hook(win, key_handle, mlx);
	mlx_loop(mlx);
}
