/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_char_to_int_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:41:03 by dvo               #+#    #+#             */
/*   Updated: 2024/06/01 20:13:41 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	ft_add_ennemy(t_cub *cub);

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
		if (!map->map[index_f])
			malloc_error(cub, true);
		i++;
		index_f++;
	}
	cub->map->max_x = max_len_table(cub->map->map);
	if (check_parcing(map, cub) == -1)
		malloc_error(cub, true);
	return (0);
}

int	convert_tab_char_to_int(t_cub *cub, int x, int y)
{
	size_t	max;

	max = max_len_table(cub->map->map);
	cub->map->max_x = max;
	while (cub->map->map[y])
	{
		cub->map->final_map[y] = ft_calloc(max, sizeof(int));
		if (!cub->map->final_map[y])
			malloc_error(cub, true);
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
	return (0);
}
