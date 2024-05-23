/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:38:02 by cassie            #+#    #+#             */
/*   Updated: 2024/05/23 16:29:11 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>
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

void  ray_draw(t_cube *cube, int x,  int h)
{
  cube->ray.lineHeight = (int)(h / cube->ray.perpWallDist);

  //calculate lowest and highest pixel to fill in current stripe
  cube->ray.drawStart = -cube->ray.lineHeight / 2 + h / 2;
  if(cube->ray.drawStart < 0) cube->ray.drawStart = 0;
  cube->ray.drawEnd = cube->ray.lineHeight / 2 + h / 2;
  if(cube->ray.drawEnd >= h) cube->ray.drawEnd = h - 1;

  //give x and y sides different brightness
  cube->ray.color = 0x00FF00;
  if(cube->ray.side == 1) {cube->ray.color = cube->ray.color / 2;}

  //draw the pixels of the stripe as a vertical line
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
    //jump to next map square, either in x-direction, or in y-direction
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
    //Check if ray has hit a wall
    //printf("|%d, %d|\n", mapX, mapY);
    if(cube->map->final_map[cube->ray.mapY][cube->ray.mapX] > 0) cube->ray.hit = 1;
    //if(worldMap[mapX][mapY] > 0) hit = 1;
  }
  if(cube->ray.side == 0) cube->ray.perpWallDist = (cube->ray.sideDistX - cube->ray.deltaDistX);
  else          cube->ray.perpWallDist = (cube->ray.sideDistY - cube->ray.deltaDistY);
}

void ray_hit(t_cube *cube)
{
  cube->ray.hit = 0; //was there a wall hit?
  //calculate step and initial sideDist
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
  cube->ray.cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
  cube->ray.rayDirX = cube->dirX + cube->planeX * cube->ray.cameraX;
  cube->ray.rayDirY = cube->dirY + cube->planeY * cube->ray.cameraX;
  //which box of the map we're in
  cube->ray.mapX = (int)cube->posX;
  cube->ray.mapY = (int)cube->posY;

  //length of ray from current position to next x or y-side

  cube->ray.deltaDistX = fabs(1 / cube->ray.rayDirX);
  cube->ray.deltaDistY = fabs(1 / cube->ray.rayDirY);
}

int raycast(t_cube *cube)
{
  int w; 
  int h;
  int x;

  w = cube->win_x;
  h = cube->win_y;
  x = -1;

    while(++x < w)
    {
      ray_position(cube, x, w);
      //calculate ray position and direction

      //what direction to step in x or y-direction (either +1 or -1)
      ray_hit(cube);
      ray_dda(cube);
      ray_draw(cube, x, h);
      //perform DDA
      //Calculate height of line to draw on screen
    }	
  return (0);
}
