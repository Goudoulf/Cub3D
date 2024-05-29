/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:41:39 by dvo               #+#    #+#             */
/*   Updated: 2024/05/29 14:48:00 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_nbr_valid(t_map *map, t_cub *cub);
int	check_wall_limit(char **str, int y, int x);

int	check_parcing(t_map *map, t_cub *cub)
{
	if (check_nbr_valid(map, cub) == -1)
		return (-1);
	return (0);
}

int	loop_check(t_map *map, int y, int x, t_cub *cub)
{
	if (map->map[y][x] == 'N' || map->map[y][x] == 'S' || \
	map->map[y][x] == 'W' || map->map[y][x] == 'E')
	{
		if (cub->ray->pos.x != 0 || cub->ray->pos.y != 0)
		{
			ft_printf(2, "too much initial position\n");
			return (-1);
		}
		cub->ray->pos.x = x;
		cub->ray->pos.y = y;
		cub->init_view = map->map[y][x];
		map->map[y][x] = '0';
	}
	else if (map->map[y][x] == '0')
	{
		if (check_wall_limit(map->map, y, x) == -1)
		{
			ft_printf(2, "map is not limited by wall at %i, %i\n", y, x);
			return (-1);
		}
	}
	else if (map->map[y][x] != '1' && map->map[y][x] != '3' && map->map[y][x] != ' ')
	{
		ft_printf(2, "%c not define on [%i][%i]\n", map->map[y][x], y, x);
		return (-1);
	}
	return (0);
}

int	check_nbr_valid(t_map *map, t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (map->map[y])
	{
		while (map->map[y][x] && map->map[y][x] != '\n')
		{
			if (loop_check(map, y, x, cub))
				return (-1);
			x++;
		}
		x = 0;
		y++;
	}
			if (!cub->init_view)
		{
			ft_printf (2, "No inital start\n");
			return (-1);
		}
	return (0);
}

int	compare_wall(char str)
{
	if (str == ' ' || str == '\n' || str == '\0')
		return (-1);
	return (0);
}

int	check_wall_limit(char **str, int y, int x)
{
	int	max_x;

	max_x = 0;
	while (str[y + 1] && str[y + 1][max_x])
		max_x++; 
	if ((!str[y][x + 1]) || compare_wall(str[y][x + 1]) == -1)
		return (-1);
	if (x == 0 || compare_wall(str[y][x - 1]) == -1)
		return (-1);
	if (x > max_x || !str[y + 1] || compare_wall(str[y + 1][x]) == -1)
		return (-1);
	if (y == 0 || compare_wall(str[y - 1][x]) == -1)
		return (-1);
	return (0);
}
