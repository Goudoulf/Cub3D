/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:37:14 by dvo               #+#    #+#             */
/*   Updated: 2024/05/30 20:47:35 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_floor_minimap(t_cub *cub);

int	init_text_map(t_cub *cub)
{
	get_floor_minimap(cub);
	return (0);
}

void	get_floor_minimap(t_cub *cub)
{
	int	y;
	int	x;
	int	offset;

	y = 0;
	while (y < cub->mini_map.y_case)
	{
		x = 0;
		while (x < cub->mini_map.x_case)
		{
			offset = (cub->texture.floor.line_len * y)
				+ (x * (cub->texture.floor.bpp / 8));
			*((unsigned int *)(offset + cub->texture.floor.buffer))
				= cub->map->floor;
			x++;
		}
		y++;
	}
}
