/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:13:02 by cassie            #+#    #+#             */
/*   Updated: 2024/06/03 07:08:30 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>
#include <stdint.h>

void	ray_draw(t_cub *cub, t_raycast *ray, int x, int h)
{
	t_tex	*tex;

	ray->line = (int)(h / ray->pvector);
	ray->start = (-ray->line >> 1) + (h >> 1);
	ray->start = (ray->start > 0) * ray->start;
	ray->end = (ray->line >> 1) + (h >> 1);
	ray->end = ((ray->end >= h) * h - 1) + (ray->end * (ray->end < h));
	ray->wall_pos = (!ray->side) * (ray->pos.y + ray->pvector * ray->vector.y)
		+ (ray->side) * (ray->pos.x + ray->pvector * ray->vector.x);
	ray->wall_pos -= floorf(ray->wall_pos);
	tex = cub->texture.tab[ray->side][(ray->vector.x > 0)][(ray->vector.y > 0)];
	ray->tex_pos.x = (int)(ray->wall_pos * 64);
	if ((!ray->side && ray->vector.x > 0) || (ray->side && ray->vector.y < 0))
		ray->tex_pos.x = ray->tex_pos.x & (64 - 1);
	while (ray->start < ray->end)
	{
		ray->tex_pos.y = (ray->start * 2 - h + ray->line) * (64 >> 1)
			/ ray->line;
		((unsigned int *)(cub->img.buffer))[x + ray->start * 1920]
			= tex_color(tex, ray->tex_pos.y, ray->tex_pos.x);
		ray->start++;
	}
}

void	ray_w_hit(t_cub *cub, t_raycast *ray)
{
	while (ray->w_hit == 0)
	{
		if (ray->next.x < ray->next.y)
		{
			ray->next.x += ray->delta.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->next.y += ray->delta.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (cub->map->final_map[cub->ray->map.y][cub->ray->map.x] == 1)
			cub->ray->w_hit = 1;
	}
	ray->pvector = (ray->side == 0) * (ray->next.x - ray->delta.x)
		+ (ray->side == 1) * (ray->next.y - ray->delta.y);
}

void	ray_direction(t_raycast *ray)
{
	ray->delta.x = fabsf(1 / ray->vector.x);
	ray->delta.y = fabsf(1 / ray->vector.y);
	ray->w_hit = 0;
	ray->step.x = ((ray->vector.x < 0) * -1) + ((ray->vector.x > 0) * 1);
	ray->step.y = ((ray->vector.y < 0) * -1) + ((ray->vector.y > 0) * 1);
	ray->next.x = (ray->vector.x < 0) * (ray->pos.x - ray->map.x) * ray->delta.x
		+ (ray->vector.x > 0) * (ray->map.x + 1.0 - ray->pos.x) * ray->delta.x;
	ray->next.y = (ray->vector.y < 0) * (ray->pos.y - ray->map.y) * ray->delta.y
		+ (ray->vector.y > 0) * (ray->map.y + 1.0 - ray->pos.y) * ray->delta.y;
}

void	ray_init(t_cub *cub, uint16_t nb_ray)
{
	float	fov_rad;
	float	angle;
	t_vec	end;

	fov_rad = cub->cam->fov_rad;
	angle = cub->cam->angle;
	end = (t_vec)
	{
		cos(angle + fov_rad) * 1.5,
		sin(angle + fov_rad) * 1.5,
	};
	cub->ray->vector = (t_vec)
	{
		cos(angle - fov_rad) * 1.5,
		sin(angle - fov_rad) * 1.5,
	};
	cub->ray->add = (t_vec)
	{
		(end.x - cub->ray->vector.x) * 1.0f / nb_ray,
		(end.y - cub->ray->vector.y) * 1.0f / nb_ray,
	};
}

int	raycast(t_cub *cub)
{
	int	x;

	x = -1;
	ray_init(cub, cub->cam->width);
	while (++x < cub->cam->width)
	{
		cub->ray->map = (t_pos)
		{
			(int)cub->ray->pos.x,
			(int)cub->ray->pos.y,
		};
		ray_direction(cub->ray);
		ray_w_hit(cub, cub->ray);
		ray_draw(cub, cub->ray, x, cub->cam->height);
		cub->ray->vector = (t_vec)
		{
			cub->ray->vector.x + cub->ray->add.x,
			cub->ray->vector.y + cub->ray->add.y,
		};
	}
	return (0);
}
