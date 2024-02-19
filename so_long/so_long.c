#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

int	key_handle(int key, void *ptr)
{
	if (key == 53)
	{
		printf("EXIT\n");
		exit(0);
	}
	return (0);
}

int main()
{
	int pixels_bits;
	int line;
	int end;
	void *mlx;
	void *img;
	int color = 0xFFE4C9;
	int y = 0;
	int x = 0;
	
	mlx = mlx_init();
	if (!mlx)
		return (1);

	img = mlx_new_image(mlx, 500, 500);
	if (!img)
		return (1);
	char *buffer = mlx_get_data_addr(img, &pixels_bits, &line, &end);
	if ( !buffer)
		return (1);
	void *win = mlx_new_window(mlx, 500, 500, "So_long");
	while (x < 500)
	{
		y = 0;
		while(y < 500)
		{
		int pixels = (y * line) + (x * 4);

		if (end == 1)
		{
			buffer[pixels + 0] = (color >> 24) & 0xFF;
			buffer[pixels + 1] = (color >> 16) & 0xFF;
			buffer[pixels + 2] = (color >> 8) & 0xFF;
			buffer[pixels + 3] = (color) & 0xFF;
		}
		else if (end == 0)
		{
			buffer[pixels + 0] = (color)& 0xFF;
			buffer[pixels + 1] = (color >> 8) & 0xFF;
			buffer[pixels + 2] = (color >> 16) & 0xFF;
			buffer[pixels + 3] = (color >> 24);
		}
		++y;
		}
		++x;
	}
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_key_hook(win, key_handle, mlx);
	mlx_loop(mlx);
	// mlx_destroy_display(mlx);
	free(mlx);
	return 0;
}