/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:04:31 by aaaraba           #+#    #+#             */
/*   Updated: 2024/03/12 21:16:21 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include "so_long.h"
#include <stdio.h>

int	key_handle(int key, t_all *all)
{
	if (key == 13)
		move_player_up(all, &all->size);
	else if (key == 1)
		move_player_down(all, &all->size);
	else if (key == 0)
		move_player_right(all, &all->size);
	else if (key == 2)
		move_player_left(all, &all->size);
	else if (key == 53)
	{
		write (1, "EXIT\n", 5);
		exit(0);
	}
	return (0);
}

void	ft_affich_imgs(t_all *all)
{
	all->i = -1;
	while (all->map_2d[++all->i] != NULL)
	{
		all->j = -1;
		while (all->map_2d[all->i][++all->j] != '\0')
		{
			if (all->map_2d[all->i][all->j] == '0')
				mlx_put_image_to_window(all->mlx, all->win,
					all->r_img, all->j * 50, all->i * 50);
			else if (all->map_2d[all->i][all->j] == '1')
				mlx_put_image_to_window(all->mlx, all->win,
					all->wall_img, all->j * 50, all->i * 50);
			else if (all->map_2d[all->i][all->j] == 'P')
				mlx_put_image_to_window(all->mlx, all->win,
					all->p_img, all->j * 50, all->i * 50);
			else if (all->map_2d[all->i][all->j] == 'E')
				mlx_put_image_to_window(all->mlx, all->win,
					all->exit_img, all->j * 50, all->i * 50);
			else if (all->map_2d[all->i][all->j] == 'C')
				mlx_put_image_to_window(all->mlx, all->win,
					all->coin_img, all->j * 50, all->i * 50);
		}
	}
}
void v()
{
    system("leaks so_long");
}
int	main(int argc, char **argv)
{
	int		fd;
	t_all	all;
	atexit(v);
	fd = 0;
	if (argc != 2)
		return (1);
	fd = open (argv[1], O_RDWR);
	all.mlx = mlx_init();
	if (!all.mlx)
		exit(1);
	all.allmap = ft_get_allmap(argv[1], fd);
	if (all.allmap == NULL)
		return (write(1, "Error\n", 6), 1);
	all.map_2d = ft_checkmap(&all);
	if (all.map_2d == NULL)
		exit(1);
	if (ft_init(&all) != 0)
		return (write(1, "Error\n", 6), 1);
	ft_position(&all);
	ft_check_access(&all, all.size.p_x, all.size.p_y);
	if (ft_cheak_map_char(&all) == 1)
		return (write(1, "Error\n", 6), 1);
	all.map_2d = ft_split(all.allmap, '\n');
	free(all.allmap);
	ft_affich_imgs(&all);
	free(all.map_2d);
	mlx_hook(all.win, 2, 0, key_handle, &all);
	mlx_hook(all.win, 17, 0, ft_exit, &all);
	mlx_loop(all.mlx);
}
