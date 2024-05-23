/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parcing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:41:39 by dvo               #+#    #+#             */
/*   Updated: 2024/05/23 10:47:22 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_nbr_valid(char **str, t_map *map);
int	check_wall_limit(char **str, size_t y, size_t x);


int	check_parcing(char **str, t_map *map)
{
	if (check_nbr_valid(str, map) == -1)
		return (-1);
	return (0);

}

int	check_nbr_valid(char **str, t_map *map)
{
	size_t y;
	size_t x;

	y = 0;
	x = 0;
	while (map->map[y])
	{
		while (map->map[y][x] && map->map[y][x] != '\n')
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S' || \
			map->map[y][x] == 'W' || map->map[y][x] == 'E')
			{
				if (map->player->init_player_x != 0 || map->player->init_player_y != 0)
				{
					ft_printf(2, "too much initial position\n");
						return (-1);
				}
				map->player->init_player_x = x;
				map->player->init_player_y = y;
				map->player->init_camera = map->map[y][x];
				map->map[y][x] = '0';
			}
			else if (map->map[y][x] == '0')
			{
				if (check_wall_limit(str, y, x) == -1)
				{
					ft_printf(2, "map is not limited by wall at %i, %i\n", y, x);
					return (-1);
				}
			}
			else if (map->map[y][x] != '1' && map->map[y][x] != ' ')
			{
				ft_printf(2, "%c not define on [%i][%i]\n", map->map[y][x], y, x);
					return (-1);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int compare_wall(char str)
{
	if (str == ' ' || str == '\n' || str == '\0')
		return (-1);
	return (0);
}

int	check_wall_limit(char **str, size_t y, size_t x)
{
	if (compare_wall(str[y][x + 1]) == -1)
		return (-1);
	if (x == 0 || compare_wall(str[y][x - 1]) == -1)
		return (-1);
	if (!str[y + 1] || compare_wall(str[y + 1][x]) == -1)
		return (-1);
	if (y == 0 || compare_wall(str[y - 1][x]) == -1)
		return (-1);
	return (0);
}
