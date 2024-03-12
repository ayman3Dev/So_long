/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:57:01 by aaaraba           #+#    #+#             */
/*   Updated: 2024/03/12 16:04:07 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player_down(t_all *all, t_size *size)
{
	size->x = size->p_x;
	size->y = size->p_y;
	if (size->p_y < size->height - 1
		&&all->map_2d[size->p_y + 1][size->p_x] != '1' &&
		!(all->map_2d[size->p_y + 1][size->p_x] == 'E' && size->coin > 0))
	{
		size->p_y++;
		ft_putdec(++all->compte_total);
		ft_putchar('\n');
	}
	ft_change_imgs(all, size);
}

void	move_player_left(t_all *all, t_size *size)
{
	size->x = size->p_x;
	size->y = size->p_y;
	if (size->p_x < size->width - 1
		&& all->map_2d[size->p_y][size->p_x + 1] != '1' &&
		!(all->map_2d[size->p_y][size->p_x + 1] == 'E' && size->coin > 0))
	{
		size->p_x++;
		ft_putdec(++all->compte_total);
		ft_putchar('\n');
	}
	ft_change_imgs(all, size);
}

void	move_player_right(t_all *all, t_size *size)
{
	size->x = size->p_x;
	size->y = size->p_y;
	if (size->p_x > 0 && all->map_2d[size->p_y][size->p_x - 1] != '1'
		&& !(all->map_2d[size->p_y][size->p_x - 1] == 'E' && size->coin > 0))
	{
		size->p_x--;
	}
	ft_change_imgs(all, size);
}

void	move_player_up(t_all *all, t_size *size)
{
	size->x = size->p_x;
	size->y = size->p_y;
	if (size->p_y > 0 && all->map_2d[size->p_y - 1][size->p_x] != '1'
		&& !(all->map_2d[size->p_y - 1][size->p_x] == 'E' && size->coin > 0))
	{
		size->p_y--;
		ft_putdec(++all->compte_total);
		ft_putchar('\n');
	}
	ft_change_imgs(all, size);
}

char	*ft_get_allmap(char *argv_one, int fd)
{
	char	*allmap;
	char	*temp;

	argv_one = get_next_line(fd);
	if (argv_one == NULL)
		return (NULL);
	while (argv_one)
	{
		temp = allmap;
		allmap = ft_strjoin(allmap, argv_one);
		free(argv_one);
		free(temp);
		argv_one = get_next_line(fd);
	}
	close (fd);
	return (allmap);
}
