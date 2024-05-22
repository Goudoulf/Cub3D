/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_final_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:43:23 by dvo               #+#    #+#             */
/*   Updated: 2024/05/22 14:30:08 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void create_final_map(t_map *map);

int	attribute_init_map(char **str, int i, int max, t_map *map)
{
	int index_f;

	map->player = ft_calloc(1, sizeof(t_position_value));
	index_f = 0;
	while (i <= max)
	{
		map->map[index_f] = ft_strdup(str[i]);
		i++;
		index_f++;
	}
	if (check_parcing(map->map, map) == -1)
	{
		free(map->player);
		return (-1);
	}
	create_final_map(map);
	return (0);
}

void create_final_map(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;

	while (map->map[y])
	{
		while (map->map[y][x] && map->map[y][x] != '\n')
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S' || \
			map->map[y][x] == 'W' || map->map[y][x] == 'E')
			{
				map->player->init_player_x = x;
				map->player->init_player_y = y;
				map->player->init_camera = map->map[y][x];
			}
			x++;
		}
		x = 0;
		y++;
	}
}
