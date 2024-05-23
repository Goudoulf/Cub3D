/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:38:02 by cassie            #+#    #+#             */
/*   Updated: 2024/05/23 17:01:56 by cassie           ###   ########.fr       */
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
    if(cube->ray.sideDistX < cube->ray.sideDistY)
    {
      cube->ray.sideDistX += cube->ray.deltaDistX;
      cube->ray.mapX += cube->ray.stepX;
      cube->ray.side = 0;
    }
    else
  {
      cube->ray.sideDistY += cube->ray.deltaDistY;
      cube->ray.mapY += cube->ray.stepY;
      cube->ray.side = 1;
    }
    if(cube->map->final_map[cube->ray.mapY][cube->ray.mapX] > 0) cube->ray.hit = 1;
  }
  if(cube->ray.side == 0) cube->ray.perpWallDist = (cube->ray.sideDistX - cube->ray.deltaDistX);
  else          cube->ray.perpWallDist = (cube->ray.sideDistY - cube->ray.deltaDistY);
}

void ray_hit(t_cube *cube)
{
  cube->ray.hit = 0;
  if(cube->ray.rayDirX < 0)
  {
    cube->ray.stepX = -1;
    cube->ray.sideDistX = (cube->posX - cube->ray.mapX) * cube->ray.deltaDistX;
  }
  else
  {
    cube->ray.stepX = 1;
    cube->ray.sideDistX = (cube->ray.mapX + 1.0 - cube->posX) * cube->ray.deltaDistX;
  }
  if(cube->ray.rayDirY < 0)
  {
    cube->ray.stepY = -1;
    cube->ray.sideDistY = (cube->posY - cube->ray.mapY) * cube->ray.deltaDistY;
  }
  else
  {
    cube->ray.stepY = 1;
    cube->ray.sideDistY = (cube->ray.mapY + 1.0 - cube->posY) * cube->ray.deltaDistY;
  }
}

void ray_position(t_cube *cube, int x, int w)
{
  cube->ray.cameraX = 2 * x / (double)w - 1;
  cube->ray.rayDirX = cube->dirX + cube->planeX * cube->ray.cameraX;
  cube->ray.rayDirY = cube->dirY + cube->planeY * cube->ray.cameraX;
  cube->ray.mapX = (int)cube->posX;
  cube->ray.mapY = (int)cube->posY;


  cube->ray.deltaDistX = fabs(1 / cube->ray.rayDirX);
  cube->ray.deltaDistY = fabs(1 / cube->ray.rayDirY);
}

void ray_init(t_cube *cube, uint16_t nb_ray)
{

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
      ray_position(cube, x, w);
      ray_hit(cube);
      ray_dda(cube);
      ray_draw(cube, x, h);
    }	
  return (0);
}
