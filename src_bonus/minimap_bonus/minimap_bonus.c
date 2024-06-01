/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:11:16 by dvo               #+#    #+#             */
/*   Updated: 2024/06/01 20:13:57 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

t_tex	*find_hero(t_cub *cub)
{
	if (!cub->texture.move)
		cub->texture.move = cub->texture.hero;
	cub->texture.move = cub->texture.move->next;
	return (cub->texture.move->tex);
}

void	put_minimap(t_cub *cub, t_pos i, t_mini_map *map, t_tex *src)
{
	t_pos	of;
	t_pos	tmp;
	t_pos	index;

	index = (t_pos){0, 0};
	tmp = (t_pos){i.x * map->x_case, i.y * map->y_case};
	while (index.y < map->y_case)
	{
		index.x = 0;
		while (index.x < map->x_case)
		{
			tmp.x = i.x * map->x_case + index.x;
			tmp.y = i.y * map->y_case + index.y;
			of.x = (map->img.line_len * tmp.y) + (tmp.x * (map->img.bpp / 8));
			of.y = (src->line_len * index.y) + (index.x * (src->bpp / 8));
			if (*((unsigned int *)(src->buffer + of.y)) != 0x00000)
				*((unsigned int *)(map->img.buffer + of.x))
					= *((unsigned int *)(src->buffer + of.y));
			else
				*((unsigned int *)(map->img.buffer + of.x))
					= *((unsigned int *)(cub->texture.floor.buffer + of.y));
			index.x++;
		}
		index.y++;
	}
}

void	ft_set_minimap(t_cub *cub, t_pos i, t_pos pos)
{
	while (i.y < 12)
	{
		i.x = 0;
		while (i.x < 12)
		{
			if (i.y == 5 && i.x == 5)
				put_minimap(cub, i, &cub->mini_map, find_hero(cub));
			else if ((i.x + pos.x < cub->map->max_x)
				&& (i.y + pos.y < cub->map->max_y)
				&& (i.x + pos.x >= 0) && (i.y + pos.y >= 0)
				&& cub->map->final_map[i.y + pos.y][i.x + pos.x] == 1)
				put_minimap(cub, i, &cub->mini_map, &cub->texture.wall);
			else if ((i.x + pos.x >= cub->map->max_x)
				|| (i.y + pos.y >= cub->map->max_y)
				|| (i.x + pos.x < 0) || (i.y + pos.y < 0))
				put_minimap(cub, i, &cub->mini_map, &cub->texture.wall);
			else
				put_minimap(cub, i, &cub->mini_map, &cub->texture.floor);
			i.x++;
		}
		i.y++;
	}
}

int	create_minimap(t_cub *cub)
{
	init_text_map(cub);
	ft_set_minimap(cub, (t_pos){0, 0}, (t_pos){(int) cub->ray->pos.x - 5,
		(int)cub->ray->pos.y - 5});
	return (1);
}
