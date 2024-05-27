/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:38:02 by cassie            #+#    #+#             */
/*   Updated: 2024/05/27 16:33:05 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>
#include <stdint.h>
#define screenWidth 1920
#define screenHeight 1080


int tex_color(t_tex *tex, int y, int x)
{
	if (x >= 0 && x < tex->width
		&& y >= 0 && y < tex->height)
	{
		return (*(int*)(tex->buffer
			+ (4 * tex->width * (int)y)
			+ (4 * (int)x)));
	}
	return (0x0);
}

void  ray_draw(t_cub *cub, int x,  int h)
{
  t_tex *tex;
  t_vec tex_pos;
  float wallX;

  cub->ray->line = (int)(h / cub->ray->pvector);
  cub->ray->start =  -cub->ray->line / 2 + h / 2;
  if(cub->ray->start < 0)
    cub->ray->start = 0;
  cub->ray->end = cub->ray->line / 2 + h / 2;
  if(cub->ray->end >= h)
    cub->ray->end = h - 1;
  if (cub->ray->side == 0)
    wallX = cub->ray->pos.y + cub->ray->pvector * cub->ray->vector.y;
  else 
    wallX = cub->ray->pos.x + cub->ray->pvector * cub->ray->vector.x;
  wallX -= floorf(wallX);
  tex_pos.x = (int)(wallX * 64);
  if (cub->ray->side == 0 && cub->ray->vector.x > 0)
    tex_pos.x = 64 - tex_pos.x - 1;
  if (cub->ray->side == 1 && cub->ray->vector.y < 0)
    tex_pos.x = 64 - tex_pos.x - 1;
  if (cub->ray->side == 0 && cub->ray->vector.x < 0)
    tex = &cub->texture.west;
  else if (cub->ray->side == 1 && cub->ray->vector.y < 0)
    tex = &cub->texture.south;
  else if (cub->ray->side == 0 && cub->ray->vector.x > 0) 
    tex = &cub->texture.east;
  else if (cub->ray->side == 1 && cub->ray->vector.y > 0)
    tex = &cub->texture.north;
  while (cub->ray->start < cub->ray->end)
  {
    tex_pos.y = (int)(cub->ray->start * 2 - 1080 + cub->ray->line) * ((64 / 2.) / cub->ray->line);
    ((unsigned int *)(cub->img.buffer))[x + cub->ray->start * 1920] = tex_color(tex, tex_pos.y, tex_pos.x);
    cub->ray->start++;
  }
}
/*ray->next.x += (ray->next.x < ray->next.y) * ray->delta.x; 
    ray->next.y += (ray->next.x > ray->next.y) * ray->delta.y;
    ray->map.x += (ray->next.x < ray->next.y) * ray->step.x;
    ray->map.y += (ray->next.x > ray->next.y) * ray->step.y;
    ray->side = (ray->next.x > ray->next.y) * 1;*/

void  ray_w_hit(t_cub *cub , t_raycast *ray)
{
   while(ray->w_hit == 0)
  {
    if(ray->next.x < ray->next.y)
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
    if(cub->map->final_map[cub->ray->map.y][cub->ray->map.x] == 1)
      cub->ray->w_hit = 1;
    if(cub->map->final_map[cub->ray->map.y][cub->ray->map.x] == 2)
    {
      cub->view_ennemy = 1;
      ray->flag_statue = 1;
      ray->statue.drawStart  = ray->start;
      ray->statue.drawEnd = ray->end;
      ray->statue.pvector = (ray->side == 0) * (ray->next.x - ray->delta.x) 
	+ (ray->side == 1) * (ray->next.y - ray->delta.y);
    }
  }
  ray->pvector = (ray->side == 0) * (ray->next.x - ray->delta.x) 
    + (ray->side == 1) * (ray->next.y - ray->delta.y);
}

void ray_direction(t_raycast *ray)
{
  ray->delta.x = fabsf(1 / ray->vector.x);
  ray->delta.y = fabsf(1 / ray->vector.y);
  ray->w_hit = 0;
  ray->flag_statue = 0;
  ray->step.x = ((ray->vector.x < 0) * -1) + ((ray->vector.x > 0) * 1);
  ray->step.y = ((ray->vector.y < 0) * -1) + ((ray->vector.y > 0) * 1);
  ray->next.x = (ray->vector.x < 0) * (ray->pos.x - ray->map.x) * ray->delta.x
    + (ray->vector.x > 0) * (ray->map.x + 1.0 - ray->pos.x) * ray->delta.x;
  ray->next.y = (ray->vector.y < 0) * (ray->pos.y - ray->map.y) * ray->delta.y 
    + (ray->vector.y > 0) * (ray->map.y + 1.0 - ray->pos.y) * ray->delta.y;
}

void ray_init(t_cub *cub, uint16_t nb_ray)
{
  float fov_rad;
  float angle;
  t_vec end;

  fov_rad = cub->cam->fov_rad;
  angle = cub->cam->angle;
  end = (t_vec)
  {
    cos(angle + fov_rad) * 1.5,
    sin(angle + fov_rad) * 1.5,
  };
  cub->ray->vector = (t_vec)
  {
    cos(angle - fov_rad)* 1.5,
    sin(angle - fov_rad)* 1.5,
  };
  cub->ray->add = (t_vec)
  {
    (end.x - cub->ray->vector.x) * 1.0f  / nb_ray,
    (end.y - cub->ray->vector.y) * 1.0f / nb_ray,
  };
}

int raycast(t_cub *cub)
{
  int x;

  x = -1;
  ray_init(cub, cub->cam->width);
  while(++x < cub->cam->width)
  {
    cub->ray->map = (t_pos)
    {
	(int)cub->ray->pos.x,
	(int)cub->ray->pos.y,
    };
    ray_direction(cub->ray);
    ray_w_hit(cub, cub->ray);
    ray_draw(cub, x, cub->cam->height);
    if (cub->ray->flag_statue == 1)
      ray_draw_statue(cub, x, cub->cam->height);
    cub->ray->vector = (t_vec)
    {
	cub->ray->vector.x + cub->ray->add.x,
	cub->ray->vector.y + cub->ray->add.y,
    };
  }	
  return (0);
}