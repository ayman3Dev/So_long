/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:57:10 by aaaraba           #+#    #+#             */
/*   Updated: 2024/03/15 02:04:39 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_position(t_all *all)
{
	all->size.p_y = -1;
	while (all->map_2d[++all->size.p_y] != NULL)
	{
		all->size.p_x = -1;
		while (all->map_2d[all->size.p_y][++all->size.p_x] != '\0')
		{
			if (all->map_2d[all->size.p_y][all->size.p_x] == 'P')
				return ;
		}
	}
}

int	ft_protect(t_all *all)
{
	if (all->win == NULL)
		return (1);
	if (all->p_img == NULL)
		return (1);
	if (all->r_img == NULL)
		return (1);
	if (all->wall_img == NULL)
		return (1);
	if (all->exit_img == NULL)
		return (1);
	if (all->coin_img == NULL)
		return (1);
	return (0);
}

int	ft_init(t_all *all)
{
	int	width;
	int	height;

	all->mlx = mlx_init();
	if (!all->mlx)
		return (close(all->fd), 1);
	all->i = 0;
	all->compte_total = 0;
	width = 0;
	height = 0;
	all->win = mlx_new_window(all->mlx, all->size.width * 50,
			all->size.height * 50, "so_long");
	all->p_img = mlx_xpm_file_to_image(all->mlx,
			"graphic/player.xpm", &width, &height);
	all->r_img = mlx_xpm_file_to_image(all->mlx,
			"graphic/route.xpm", &width, &height);
	all->wall_img = mlx_xpm_file_to_image(all->mlx,
			"graphic/wall.xpm", &width, &height);
	all->exit_img = mlx_xpm_file_to_image(all->mlx,
			"graphic/Door.xpm", &width, &height);
	all->coin_img = mlx_xpm_file_to_image(all->mlx,
			"graphic/coin.xpm", &width, &height);
	return (ft_protect(all));
}

void	ft_change_imgs(t_all *all, t_size *size)
{
	if (all->map_2d_copy[size->p_y][size->p_x] == 'E' && size->coin == 0)
	{
		mlx_put_image_to_window(all->mlx, all->win,
			all->r_img, size->x * 50, size->y * 50);
		ft_free(all->map_2d_copy);
		exit(0);
	}
	else
	{
		if (all->map_2d_copy[size->p_y][size->p_x] == 'C')
		{
			all->map_2d_copy[size->p_y][size->p_x] = '0';
			size->coin--;
		}
		mlx_put_image_to_window(all->mlx, all->win,
			all->r_img, size->x * 50, size->y * 50);
		mlx_put_image_to_window(all->mlx, all->win,
			all->p_img, size->p_x * 50, size->p_y * 50);
	}
}

int	ft_exit(t_all *all)
{
	mlx_destroy_window(all->mlx, all->win);
	mlx_destroy_image(all->mlx, all->coin_img);
	mlx_destroy_image(all->mlx, all->p_img);
	mlx_destroy_image(all->mlx, all->r_img);
	mlx_destroy_image(all->mlx, all->wall_img);
	mlx_destroy_image(all->mlx, all->exit_img);
	ft_free(all->map_2d_copy);
	exit(0);
	return (0);
}
