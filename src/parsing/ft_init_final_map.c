/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_final_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:43:23 by dvo               #+#    #+#             */
/*   Updated: 2024/05/29 13:40:21 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t	max_len_table(char **str)
{
	size_t	len;
	size_t	x;
	size_t	y;

	len = 0;
	x = 0;
	y = 0;
	while (str[y])
	{
		while (str[y][x] != '\0')
			x++;
		if (x > len)
			len = x;
		x = 0;
		y++;
	}
	return (len);
}

int	attribute_init_map(int i, int max, t_map *map, t_cub *cub)
{
	int	index_f;

	index_f = 0;
	while (i <= max)
	{
		map->map[index_f] = ft_strdup(map->buffer[i]);
		i++;
		index_f++;
	}
	cub->map->max_X = max_len_table(cub->map->map);
	if (check_parcing(map, cub) == -1)
		return (-1);
	return (0);
}

int convert_tab_char_to_int(t_cub *cub)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (cub->map->map[y])
	{
		cub->map->final_map[y] = ft_calloc(cub->map->max_X, sizeof(int));
		while (cub->map->map[y][x] != '\0')
		{
			if (cub->map->map[y][x] != '0')
				cub->map->final_map[y][x] = 1;
			if (cub->map->map[y][x] == '3')
				cub->map->final_map[y][x] = -1;
			x++;
		}
		x = 0;
		y++;
	}
	ft_add_ennemy(cub);
	return (0);
}