/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:02:22 by aaaraba           #+#    #+#             */
/*   Updated: 2024/03/12 21:09:54 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_check(char *allmap, t_size *size)
{
	int	i;

	size->player = 0;
	size->coin = 0;
	size->door = 0;
	i = 0;
	while (allmap[i] != '\0')
	{
		if ((allmap[i] == '\n' && allmap[i + 1] == '\n') || allmap[0] != '1')
			return (ft_putstr("ERROR"), 1);
		if (allmap[i] != 'P' && allmap[i] != 'E' && allmap[i] != 'C'
			&& allmap[i] != '\n' && allmap[i] != '0' && allmap[i] != '1')
			return (write (1, "Error", 5), 1);
		if (allmap[i] == 'P')
			size->player++;
		if (allmap[i] == 'C')
			size->coin++;
		if (allmap[i] == 'E')
			size->door++;
		i++;
	}
	size->coin_check = size->coin;
	if (size->player != 1 || size->coin < 1
		|| size->door != 1 || allmap[--i] != '1')
		return (ft_putstr("ERROR"), 1);
	return (0);
}

int	ft_check_lenght(char *allmap)
{
	int	i;
	int	j;
	int	temp_width;
	int	width_map;

	i = 0;
	j = 0;
	temp_width = 0;
	width_map = 0;
	while (allmap[i] != '\0')
	{
		if (allmap[i] == '\n' || allmap[i] == '\0')
		{
			temp_width = i - j + 1;
			j = i + 1;
		}
		if (width_map == 0)
			width_map = temp_width;
		else if (width_map != temp_width)
			return (write(1, "Error\n", 6), 1);
		i++;
	}
	return (0);
}

char	**ft_checkmap(t_all *all)
{
	all->size.height = 0;
	all->size.width = 0;
	if (ft_check(all->allmap, &all->size) != 0
		|| ft_check_lenght(all->allmap) != 0)
		exit(1);
	all->map_2d = ft_split(all->allmap, '\n');
	all->size.width = strlen(all->map_2d[0]);
	while (all->map_2d[all->size.height] != NULL)
		all->size.height++;
	while (all->map_2d[0][all->i] != '\0'
		&& all->map_2d[all->size.height - 1][all->i] != '\0')
	{
		if (all->map_2d[0][all->i] != '1'
			|| all->map_2d[all->size.height - 1][all->i] != '1')
			return (write (1, "ERROR", 5), NULL);
		all->i++;
	}
	all->j = -1;
	while (++all->j < all->size.height)
	{
		if (all->map_2d[all->j][0] != '1'
			|| all->map_2d[all->j][all->size.width - 1] != '1')
			return (write (1, "ERROR", 5), NULL);
	}
	return (all->map_2d);
}

int	ft_cheak_map_char(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (all->size.height == all->size.width)
		return (1);
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
	if (all->size.coin_check <= 0 && all->size.door == 0 && all->map_2d[y][x] == 'x')
	{
		return (1);
	}
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

// int	ft_check_access(t_all *all, int x, int y)
// {
// 	printf("\ncoin_check: %d	c: %c\n", all->size.coin_check, all->map_2d[y][x]);
// 	if (all->map_2d[y][x] == 'P')
// 		all->map_2d[y][x] = '0';
// 	if (all->map_2d[y][x] == 'C')
// 	{
// 		all->size.coin_check--;
// 		all->map_2d[y][x] = '0';
// 	}
// 	if (all->map_2d[y][x] == 'E' && all->size.door == 1)
// 		all->size.door--;
// 	if (all->map_2d[y][x] == 'E' && all->size.coin_check <= 0 && all->size.door <= 0)
// 	{
// 		all->map_2d[y][x] = '0';
// 		return (1);
// 	}
// 	if (all->map_2d[y][x] == '0')
// 	{
// 		all->map_2d[y][x] = '1';
// 		if (ft_check_access(all, (x - 1), y) == 1
// 			|| ft_check_access(all, (x + 1), y) == 1
// 			|| ft_check_access(all, x, (y - 1)) == 1
// 			|| ft_check_access(all, x, (y + 1)) == 1)
// 			return (1);
// 	}
// 	return (0);
// }