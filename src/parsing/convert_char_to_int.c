/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_char_to_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:41:03 by dvo               #+#    #+#             */
/*   Updated: 2024/05/28 14:14:03 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int convert_tab_char_to_int(t_cub *cub)
{
	size_t	max;
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	max = max_len_table(cub->map->map);
	cub->map->max_X = max;
	printf("%zu : max_X\n", max);
	while (cub->map->map[y])
	{
		cub->map->final_map[y] = ft_calloc(max, sizeof(int));
		while (cub->map->map[y][x] != '\0')
		{
			if (cub->map->map[y][x] == '1')
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

void	ft_add_ennemy(t_cub *cub)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (y < cub->map->max_Y)
	{
		while (x < cub->map->max_X)
		{
			if (cub->map->final_map[y][x] == 0)
			{
				cub->map->final_map[y][x] = 2;
				cub->posX_ennemy = x;
				cub->posY_ennemy = y;
				return ;
			}
			x++;
		}
		y++;
		x = 0;
	}

}
