/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:38:02 by cassie            #+#    #+#             */
/*   Updated: 2024/05/25 19:35:53 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>
#include <stdint.h>
#define screenWidth 1920
#define screenHeight 1080
#define mapWidth 24
#define mapHeight 24

int
	get_tex_color(t_tex *tex, int y, int x)
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
  t_tex *tex = NULL;
  cub->ray.lineHeight = (int)(h / cub->ray.perpWallDist);

  cub->ray.drawStart = -cub->ray.lineHeight / 2 + h / 2;
  if(cub->ray.drawStart < 0)
    cub->ray.drawStart = 0;
  cub->ray.drawEnd = cub->ray.lineHeight / 2 + h / 2;
  if(cub->ray.drawEnd >= h)
    cub->ray.drawEnd = h - 1;

  cub->ray.color = 0x00FF00;
  if(cub->ray.side == 1)
    cub->ray.color = cub->ray.color / 2;

  float wallX;
  if (cub->ray.side == 0) wallX = cub->ray.pos.y + cub->ray.perpWallDist * cub->ray.rayDir.y;
  else wallX = cub->ray.pos.x + cub->ray.perpWallDist * cub->ray.rayDir.x;
  wallX -= floorf(wallX);

  int texX = (int)(wallX * 64);
  if (cub->ray.side == 0 && cub->ray.rayDir.x > 0) texX = 64 - texX - 1;
  if (cub->ray.side == 1 && cub->ray.rayDir.y < 0) texX = 64 - texX - 1;
  if (cub->ray.side == 0 ) tex = &cub->texture.north;
  if (cub->ray.side == 1 ) tex = &cub->texture.south;
 // float step = 1.0 * 64 / cub->ray.lineHeight;
 // float texPos = (cub->ray.drawStart - (float)h / 2 + (float)cub->ray.lineHeight / 2) * step;
  while (cub->ray.drawStart < cub->ray.drawEnd)
  {
      //int texY = (int)texPos & (64 - 1);
      int texY = (int)(cub->ray.drawStart * 2 - 1080 + cub->ray.lineHeight) * ((64 / 2.) / cub->ray.lineHeight);
      //texPos += step;
//      uint32_t color = cub->texture.north.buffer[64 * texY + texX];
//    my_mlx_pixel_put(&cub->img, x, cub->ray.drawStart, cub->ray.color);
//  ((unsigned int *)(cub->img.buffer))[x + cub->ray.drawStart * 1920] = cub->ray.color;
  ((unsigned int *)(cub->img.buffer))[x + cub->ray.drawStart * 1920] = get_tex_color(tex, texY, texX);
    cub->ray.drawStart++;
  }
}

void  ray_dda(t_cub *cub)
{
  while(cub->ray.hit == 0)
  {
    if(cub->ray.sideDist.x < cub->ray.sideDist.y)
    {
      cub->ray.sideDist.x += cub->ray.deltaDist.x;
      cub->ray.map.x += cub->ray.step.x;
      cub->ray.side = 0;
    }
    else
    {
      cub->ray.sideDist.y += cub->ray.deltaDist.y;
      cub->ray.map.y += cub->ray.step.y;
      cub->ray.side = 1;
    }
    if(cub->map->final_map[cub->ray.map.y][cub->ray.map.x] > 0)
      cub->ray.hit = 1;
  }
  if(cub->ray.side == 0)
    cub->ray.perpWallDist = (cub->ray.sideDist.x - cub->ray.deltaDist.x);
  else
    cub->ray.perpWallDist = (cub->ray.sideDist.y - cub->ray.deltaDist.y);
}

void ray_hit(t_cub *cub)
{
  cub->ray.deltaDist.x = fabsf(1 / cub->ray.rayDir.x);
  cub->ray.deltaDist.y = fabsf(1 / cub->ray.rayDir.y);
  cub->ray.hit = 0;
  if(cub->ray.rayDir.x < 0)
  {
    cub->ray.step.x = -1;
    cub->ray.sideDist.x = (cub->ray.pos.x - cub->ray.map.x) * cub->ray.deltaDist.x;
  }
  else
  {
    cub->ray.step.x = 1;
    cub->ray.sideDist.x = (cub->ray.map.x + 1.0 - cub->ray.pos.x) * cub->ray.deltaDist.x;
  }
  if(cub->ray.rayDir.y < 0)
  {
    cub->ray.step.y = -1;
    cub->ray.sideDist.y = (cub->ray.pos.y - cub->ray.map.y) * cub->ray.deltaDist.y;
  }
  else
  {
    cub->ray.step.y = 1;
    cub->ray.sideDist.y = (cub->ray.map.y + 1.0 - cub->ray.pos.y) * cub->ray.deltaDist.y;
  }
}

void ray_init(t_cub *cub, uint16_t nb_ray)
{
  float fov_rad;
  float angle;
  t_vec end;

  fov_rad = cub->cam.fov_rad;
  angle = cub->cam.angle;
  end = (t_vec)
  {
    cos(angle + fov_rad) ,
    sin(angle + fov_rad),
  };
  cub->ray.rayDir = (t_vec)
  {
    cos(angle - fov_rad),
    sin(angle - fov_rad),
  };
  cub->ray.add = (t_vec)
  {
    (end.x - cub->ray.rayDir.x) * 1.0f  / nb_ray,
    (end.y - cub->ray.rayDir.y) * 1.0f / nb_ray,
  };
}

int raycast(t_cub *cub)
{
  int x;

  x = -1;
  ray_init(cub, cub->cam.width);
  while(++x < cub->cam.width)
  {
    cub->ray.map = (t_pos)
    {
	(int)cub->ray.pos.x,
	(int)cub->ray.pos.y,
    };
    ray_hit(cub);
    ray_dda(cub);
    ray_draw(cub, x, cub->cam.height);
    cub->ray.rayDir = (t_vec)
    {
	cub->ray.rayDir.x + cub->ray.add.x,
	cub->ray.rayDir.y + cub->ray.add.y,
    };
  }	
  return (0);
}
