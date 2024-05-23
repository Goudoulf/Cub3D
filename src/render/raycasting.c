/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:38:02 by cassie            #+#    #+#             */
/*   Updated: 2024/05/23 20:48:20 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>
#include <stdint.h>
#define screenWidth 800
#define screenHeight 600
#define mapWidth 24
#define mapHeight 24

/*int worldMap[mapWidth][mapHeight]=
{
   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
 };*/

/*void  texture_calc(t_cube *cube)
{
  int textNum;


}*/

void  ray_draw(t_cube *cube, int x,  int h)
{
  cube->ray.lineHeight = (int)(h / cube->ray.perpWallDist);

  cube->ray.drawStart = -cube->ray.lineHeight / 2 + h / 2;
  if(cube->ray.drawStart < 0) cube->ray.drawStart = 0;
  cube->ray.drawEnd = cube->ray.lineHeight / 2 + h / 2;
  if(cube->ray.drawEnd >= h) cube->ray.drawEnd = h - 1;

  cube->ray.color = 0x00FF00;
  if(cube->ray.side == 1) {cube->ray.color = cube->ray.color / 2;}

  while (cube->ray.drawStart < cube->ray.drawEnd)
  {
    my_mlx_pixel_put(&cube->img, x, cube->ray.drawStart, cube->ray.color);
    cube->ray.drawStart++;
  }
}

void  ray_dda(t_cube *cube)
{
  while(cube->ray.hit == 0)
  {
    if(cube->ray.sideDist.x < cube->ray.sideDist.y)
    {
      cube->ray.sideDist.x += cube->ray.deltaDist.x;
      cube->ray.map.x += cube->ray.step.x;
      cube->ray.side = 0;
    }
    else
  {
      cube->ray.sideDist.y += cube->ray.deltaDist.y;
      cube->ray.map.y += cube->ray.step.y;
      cube->ray.side = 1;
    }
    printf("mapx=%d\n", cube->ray.map.x);
    printf("mapy=%d\n", cube->ray.map.y);
    if(cube->map->final_map[cube->ray.map.y][cube->ray.map.x] > 0) cube->ray.hit = 1;
  }
  if(cube->ray.side == 0) cube->ray.perpWallDist = (cube->ray.sideDist.x - cube->ray.deltaDist.x);
  else          cube->ray.perpWallDist = (cube->ray.sideDist.y - cube->ray.deltaDist.y);
}

void ray_hit(t_cube *cube)
{
  cube->ray.deltaDist.x = fabs(1 / cube->ray.rayDir.x);
  cube->ray.deltaDist.y = fabs(1 / cube->ray.rayDir.y);
  cube->ray.hit = 0;
  if(cube->ray.rayDir.x < 0)
  {
    cube->ray.step.x = -1;
    cube->ray.sideDist.x = (cube->pos.x - cube->ray.map.x) * cube->ray.deltaDist.x;
  }
  else
  {
    cube->ray.step.x = 1;
    cube->ray.sideDist.x = (cube->ray.map.x + 1.0 - cube->pos.x) * cube->ray.deltaDist.x;
  }
  if(cube->ray.rayDir.y < 0)
  {
    cube->ray.step.y = -1;
    cube->ray.sideDist.y = (cube->pos.y - cube->ray.map.y) * cube->ray.deltaDist.y;
  }
  else
  {
    cube->ray.step.y = 1;
    cube->ray.sideDist.y = (cube->ray.map.y + 1.0 - cube->pos.y) * cube->ray.deltaDist.y;
  }
}

/*void ray_position(t_cube *cube, int x, int w)
{
  cube->ray.cameraX = 2 * x / (double)w - 1;
  cube->ray.rayDirX = cube->dirX + cube->planeX * cube->ray.cameraX;
  cube->ray.rayDirY = cube->dirY + cube->planeY * cube->ray.cameraX;
  cube->ray.mapX = (int)cube->posX;
  cube->ray.mapY = (int)cube->posY;


}*/

void ray_init(t_cube *cube, uint16_t nb_ray)
{
  double tutu = 90 * M_PI * 0.5 / 180.0;
  double angle = - M_PI / 2;
  const t_vec	end = (t_vec){
    cos(angle + tutu),
    sin(angle + tutu),
  };
  cube->ray.rayDir = (t_vec){
    cos(angle - tutu),
    sin(angle - tutu),
  };
  cube->ray.add = (t_vec){
    (end.x - cube->ray.rayDir.x) / nb_ray,
    (end.y - cube->ray.rayDir.y) / nb_ray,
  };
  cube->ray.map = (t_pos){
      (int)cube->pos.x,
      (int)cube->pos.y,
  };

  printf("map=%d\n", cube->map->final_map[0][0]);
  printf("mapx=%d\n", cube->ray.map.x);
  printf("mapy=%d\n", cube->ray.map.y);
}

int raycast(t_cube *cube)
{
  int w; 
  int h;
  int x;

  w = 800;
  h = 600;
  x = -1;

    ray_init(cube, 800);
    while(++x < w)
    {
//      ray_position(cube, x, w);
      ray_hit(cube);
      ray_dda(cube);
      ray_draw(cube, x, h);
      cube->ray.rayDir = (t_vec)
      {
	cube->ray.rayDir.x + cube->ray.add.x,
	cube->ray.rayDir.y + cube->ray.add.y,
      };
    }	
  return (0);
}
