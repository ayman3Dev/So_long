/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:02:22 by aaaraba           #+#    #+#             */
/*   Updated: 2024/03/21 05:46:30 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int	ft_check(char *allmap, t_size *size)
{
	int	i;

	size->player = 0;
	size->coin = 0;
	size->door = 0;
	i = -1;
	while (allmap[++i] != '\0')
	{
		if ((allmap[i] == '\n' && allmap[i + 1] == '\n'))
			return (write(1, "Error\nInvalid map\n", 18), 1);
		if (allmap[i] != 'P' && allmap[i] != 'E' && allmap[i] != 'C'
			&& allmap[i] != '\n' && allmap[i] != '0' && allmap[i] != '1')
			return (write (1, "Error\nInvalid map\n", 18), 1);
		if (allmap[i] == 'P')
			++size->player;
		if (allmap[i] == 'C')
			++size->coin;
		if (allmap[i] == 'E')
			++size->door;
	}
	size->coin_check = size->coin;
	if (size->player != 1 || size->coin < 1
		|| size->door != 1 || allmap[i - 1] == '\n')
		return (write(1, "Error\nInvalid map\n", 18), 1);
	return (0);
}

int	ft_check_lenght(t_all *all)
{
	all->i = 0;
	all->size.height = 0;
	all->size.width = 0;
	if (all->allmap[0] == '\n')
		return (write(1, "Error\nInvalid map\n", 18), 1);
	all->map_2d = ft_split(all->allmap, '\n');
	all->size.width = ft_strlen(all->map_2d[0]);
	while (all->map_2d[all->size.height] != NULL)
	{
		if ((int)ft_strlen(all->map_2d[all->size.height]) != all->size.width)
			return (write(1, "Error\nInvalid map\n", 18), 1);
		all->size.height++;
	}
	if (all->size.height > 28 || all->size.width > 51)
	{
		free(all->allmap), ft_free(all->map_2d);
		write (1, "map too long", 12);
		exit(1);
	}
	return (0);
}

char	**ft_checkmap(t_all *all)
{
	if (ft_check(all->allmap, &all->size) != 0
		|| ft_check_lenght(all) != 0)
		return (NULL);
	all->i = 0;
	while (all->map_2d[0][all->i] != '\0'
		&& all->map_2d[all->size.height - 1][all->i] != '\0')
	{
		if (all->map_2d[0][all->i] != '1'
			|| all->map_2d[all->size.height - 1][all->i] != '1')
			return (write(1, "Error\nInvalid map\n", 18), NULL);
		all->i++;
	}
	all->j = -1;
	while (++all->j < all->size.height)
	{
		if (all->map_2d[all->j][0] != '1'
			|| all->map_2d[all->j][all->size.width - 1] != '1')
			return (write(1, "Error\nInvalid map\n", 18), NULL);
	}
	return (all->map_2d);
}

int	ft_cheak_map_char(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (all->map_2d[i] != NULL)
	{
		j = 0;
		while (all->map_2d[i][j] != '\0')
		{
			if (all->map_2d[i][j] == 'C' || all->map_2d[i][j] == 'E')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_access(t_all *all, int x, int y)
{
	if (all->map_2d[y][x] == 'P')
		all->map_2d[y][x] = '0';
	if (all->map_2d[y][x] == 'C')
	{
		all->size.coin_check--;
		all->map_2d[y][x] = '0';
	}
	if (all->map_2d[y][x] == 'E' && all->size.door == 1)
	{
		all->map_2d[y][x] = 'x';
		all->size.door--;
	}
	if (all->size.coin_check <= 0 && all->size.door == 0
		&& all->map_2d[y][x] == 'x')
		return (1);
	if (all->map_2d[y][x] == '0')
	{
		all->map_2d[y][x] = '1';
		if (ft_check_access(all, (x - 1), y) == 1
			|| ft_check_access(all, (x + 1), y) == 1
			|| ft_check_access(all, x, (y - 1)) == 1
			|| ft_check_access(all, x, (y + 1)) == 1)
			return (1);
	}
	return (0);
}
 