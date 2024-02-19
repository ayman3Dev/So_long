#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <string.h>

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
	//int map[MAP_HEIGHT][MAP_WIDTH];
	int height = 0;
	int width = 0;
	char *new;
	int c = 1;
	int fd = open ("map.ber", O_RDWR);
	char *allmap;
	int line_width;
	int line_number =  0;
	void *mlx = mlx_init();
	if (!mlx)
		return (1);
	allmap = get_next_line(fd);
	int width_map = strlen(allmap) - 1;
	int height_map = 1;
	while (allmap)
	{
		allmap = get_next_line(fd);
		if(allmap == NULL)
			break;
		height_map++;
	}
	close(fd);
	allmap = NULL;
	fd = open ("map.ber", O_RDWR);
	void *win = mlx_new_window(mlx, width_map * 50, height_map * 50, "so_long");

	void *player_img = mlx_xpm_file_to_image(mlx, "so_long/Graphic/playerr.xpm", &width , &height);
	void *route_img = mlx_xpm_file_to_image(mlx, "so_long/Graphic/texturee.xpm", &width , &height);
	void *wall_img = mlx_xpm_file_to_image(mlx, "so_long/Graphic/wall1708384213.xpm", &width , &height);

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


// char **str = ft_split();
// int height;
// int weidth;

// weidth = ft_strlen(str[0]);
// while(str[x])
// 	x++;