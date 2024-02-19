#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

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
	int y;
	int x;
	int texture_x, texture_y;
	int player_x, playe_y;
	void *mlx = mlx_init();
	if (!mlx)
		return (1);
	void *win = mlx_new_window(mlx, 1000, 1000, "so_long");

	void *player_img = mlx_xpm_file_to_image(mlx, "so_long/Graphic/player.xpm", &x , &y);
	void *texture_img = mlx_xpm_file_to_image(mlx, "so_long/Graphic/texture.xpm", &x, &y);

	mlx_put_image_to_window(mlx, win, texture_img, texture_x , texture_y);
	mlx_put_image_to_window(mlx, win, player_img, playe_y , player_x );
	
	mlx_key_hook(win, key_handle, mlx);
	mlx_loop(mlx);
}