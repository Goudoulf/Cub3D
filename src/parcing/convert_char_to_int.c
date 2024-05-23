/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_char_to_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:41:03 by dvo               #+#    #+#             */
/*   Updated: 2024/05/23 16:21:12 by dvo              ###   ########.fr       */
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

int	convert_tab_char_to_int(t_cube *cube)
{
	size_t	max;
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	max = max_len_table(cube->map->map);
	cube->map->max_X = max;
	printf("%zu : max_X\n", max);
	while (cube->map->map[y])
	{
		cube->map->final_map[y] = ft_calloc(max, sizeof(int));
		while (cube->map->map[y][x] != '\0')
		{
			if (cube->map->map[y][x] == '1')
				cube->map->final_map[y][x] = 1;
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}
