#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 10



int key_handle(int key, void *ptr)
{
    if (key == 53)
    {
        printf("EXIT\n");
        exit(0);
    }
    return (0);
}

int main(int argc, char **argv)
{
    void *mlx;
    void *img;
    int y = 0;
    int x = 0;
    int height = 500;
    int width = 500;
    
    int map[MAP_HEIGHT][MAP_WIDTH + 1];
    mlx = mlx_init();
    if (!mlx)
        return (1);
    img = mlx_xpm_file_to_image(mlx, "so_long/texture/lava.xpm", &height, &width);
    if (!img)
        return (1);
    // char *buffer = mlx_get_data_addr(img, &pixels_bits, &line, &end);
    // if ( !buffer)
    //  return (1);
    void *win = mlx_new_window(mlx, MAP_WIDTH * 50, MAP_HEIGHT * 50, "So_long");
    if (!win)
        return (1);
    // while (y < MAP_HEIGHT)
    // {
    //     while (x < MAP_WIDTH)
    //     {
    //         if(map[y][x] == 1)
    //             mlx_string_put(mlx, win, x * 50, y * 50, 0xFF, "V");
    //         else if(map[y][x] == 0){
    //             mlx_string_put(mlx, win, x * 50, y * 50, 0xFF, ".");
    //         }
    //         x++;
    //     }
    //     y++;
    // }
    
    mlx_put_image_to_window(mlx, win, img, 0, 0);
    mlx_key_hook(win, key_handle, mlx);
    mlx_loop(mlx);
    // mlx_destroy_display(mlx);
    free(mlx);
    return 0;
}