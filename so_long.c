/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:04:31 by aaaraba           #+#    #+#             */
/*   Updated: 2024/03/16 05:14:33 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_handle(int key, t_all *all)
{
	if (key == 53)
	{
		write (1, "EXIT\n", 5);
		ft_free(all->map_2d_copy);
		exit(0);
	}
	else if (key == 13 || key == 126)
		move_player_up(all, &all->size);
	else if (key == 1 || key == 125)
		move_player_down(all, &all->size);
	else if (key == 0 || key == 123)
		move_player_right(all, &all->size);
	else if (key == 2 || key == 124)
		move_player_left(all, &all->size);
	return (0);
}

void	ft_affich_imgs(t_all *all)
{
	all->i = -1;
	while (all->map_2d_copy[++all->i] != NULL)
	{
		all->j = -1;
		while (all->map_2d_copy[all->i][++all->j] != '\0')
		{
			if (all->map_2d_copy[all->i][all->j] == '0')
				mlx_put_image_to_window(all->mlx, all->win,
					all->r_img, all->j * 50, all->i * 50);
			else if (all->map_2d_copy[all->i][all->j] == '1')
				mlx_put_image_to_window(all->mlx, all->win,
					all->wall_img, all->j * 50, all->i * 50);
			else if (all->map_2d_copy[all->i][all->j] == 'P')
				mlx_put_image_to_window(all->mlx, all->win,
					all->p_img, all->j * 50, all->i * 50);
			else if (all->map_2d_copy[all->i][all->j] == 'E')
				mlx_put_image_to_window(all->mlx, all->win,
					all->exit_img, all->j * 50, all->i * 50);
			else if (all->map_2d_copy[all->i][all->j] == 'C')
				mlx_put_image_to_window(all->mlx, all->win,
					all->coin_img, all->j * 50, all->i * 50);
		}
	}
}

void	ft_free(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	ft_free_all(t_all *all)
{
	if (all->p_img != NULL)
		mlx_destroy_image(all->mlx, all->p_img);
	if (all->r_img != NULL)
		mlx_destroy_image(all->mlx, all->r_img);
	if (all->wall_img != NULL)
		mlx_destroy_image(all->mlx, all->wall_img);
	if (all->coin_img != NULL)
		mlx_destroy_image(all->mlx, all->coin_img);
	if (all->exit_img != NULL)
		mlx_destroy_image(all->mlx, all->exit_img);
	if (all->win != NULL)
		mlx_destroy_window(all->mlx, all->win);
	free(all->allmap);
	ft_free(all->map_2d);
	ft_free(all->map_2d_copy);
	write(1, "Error\n", 6);
	exit(1);
}

void	v(void)
{
	system("leaks so_long");
}

int	main(int argc, char **argv)
{
	t_all	all;

	atexit(v);
	if (argc != 2)
		return (1);
	all.allmap = ft_get_allmap(argv[1], &all);
	if (all.allmap == NULL)
		return (write(1, "Error\n", 6), 1);
	if (!ft_checkmap(&all))
		return (free(all.allmap), ft_free(all.map_2d), 1);
	if (ft_init(&all) == 1)
		return (ft_free_all(&all), 1);
	ft_position(&all);
	ft_check_access(&all, all.size.p_x, all.size.p_y);
	if (ft_cheak_map_char(&all))
		ft_free_all(&all);
	ft_free(all.map_2d);
	all.map_2d_copy = ft_split(all.allmap, '\n');
	if (!all.map_2d_copy)
		return (free(all.allmap), 1);
	ft_affich_imgs(&all);
	free(all.allmap);
	mlx_hook(all.win, 2, 0, key_handle, &all);
	mlx_hook(all.win, 17, 0, ft_exit, &all);
	mlx_loop(all.mlx);
}
