/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_ennemy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:13:29 by dvo               #+#    #+#             */
/*   Updated: 2024/05/28 15:41:00 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
# include <sys/time.h>

void    ft_ennemy_move(t_cub *cub)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (cub->view_ennemy == 1 || (tv.tv_sec * 1000000 + tv.tv_usec) < cub->fps_statue)
		return ;
	cub->fps_statue = cub->view_ennemy == 1 && (tv.tv_sec * 1000000 + tv.tv_usec) + 1000000;
	ft_sonar(cub, cub->map->final_map);
}

void ray_draw_statue(t_cub *cub, int x, int h)
{
	t_tex *tex = &cub->texture.statue;
	int lineHeight = (int)(h / cub->ray->statue.pvector);

	int drawStart = -lineHeight / 2 + h / 2;
	if (drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + h / 2;
	if (drawEnd >= h)
		drawEnd = h - 1;

	float wallX;
	if (cub->ray->statue.side == 0)
		wallX = cub->ray->pos.y + cub->ray->statue.pvector * cub->ray->vector.y;
	else
		wallX = cub->ray->pos.x + cub->ray->statue.pvector * cub->ray->vector.x;
	wallX -= floorf(wallX);

	int texX = (int)(wallX * 64);
	if (cub->ray->statue.side == 0 && cub->ray->vector.x > 0) texX = 64 - texX - 1;
	if (cub->ray->statue.side == 1 && cub->ray->vector.y < 0) texX = 64 - texX - 1;
	if (cub->ray->side == 0 && cub->ray->vector.x < 0) tex = &cub->texture.statue;
	if (cub->ray->side == 1 && cub->ray->vector.y < 0) tex = &cub->texture.statue;
	if (cub->ray->side == 0 && cub->ray->vector.x > 0) tex = &cub->texture.statue;
	if (cub->ray->side == 1 && cub->ray->vector.y > 0) tex = &cub->texture.statue;

	while (drawStart < drawEnd)
	{
		int texY = (int)(drawStart * 2 - h + lineHeight) * ((64 / 2.) / lineHeight);
		unsigned int color = tex_color(tex, texY, texX);

		if (color != 0x000000)
		{
			((unsigned int *)(cub->img.buffer))[x + drawStart * 1920] = color;
		}
		drawStart++;
	}
}
