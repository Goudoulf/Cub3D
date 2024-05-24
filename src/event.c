/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:54:00 by cassie            #+#    #+#             */
/*   Updated: 2024/05/24 16:41:10 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>
#include <stdio.h>

int	close_window(t_cube *cube)
{
	mlx_destroy_image(cube->mlx, cube->img.img_ptr);
	mlx_destroy_window(cube->mlx, cube->win);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
	exit(EXIT_SUCCESS);
}

int	key_control(int keycode, t_cube *cube)
{
	cube->ray.move.x = 0;
	cube->ray.move.y = 0;
	if (keycode == XK_Escape)
		close_window(cube);
	if (keycode == XK_w)
	{
		//if (cube->pos.y + y <= cube->map->max_X - 1 && cube->pos.y + y >= 1)
		//	cube->pos.y += y;
		//check_hit_wall(cube, 0);
		cube->ray.move.x += 0.05;
	}
	if (keycode == XK_s)
	{
		cube->ray.move.x -= 0.05;
		//if (cube->pos.y - y <= cube->map->max_X - 1 && cube->pos.y - y >= 1)
		//	cube->pos.y -= y;
		printf("posX=%f\n", cube->pos.x);
		printf("posY=%f\n", cube->pos.y);
	}
	if (keycode == XK_a)
	{
		cube->ray.move.y -= 0.05;
	}
	if (keycode == XK_d)
	{
		cube->ray.move.y += 0.05;
	}
	if (keycode == XK_Left)
	{
		cube->ray.angle -= 0.05;
	}
	if (keycode == XK_Right)
	{
		cube->ray.angle += 0.05;
	}
/*	if (keycode == XK_d)
	{
		double oldDirX = cube->dirX;
		cube->dirX = cube->dirX * cos(-0.02) - cube->dirY * sin(-0.02);
		cube->dirY = oldDirX * sin(-0.02) + cube->dirY * cos(-0.02);
		double oldPlaneX = cube->planeX;
		cube->planeX = cube->planeX * cos(-0.02) - cube->planeY * sin(-0.02);
		cube->planeY = oldPlaneX * sin(-0.02) + cube->planeY * cos(-0.02);
	}
	if (keycode == XK_a)
	{
		double oldDirX = cube->dirX;
		cube->dirX = cube->dirX * cos(0.02) - cube->dirY * sin(0.02);
		cube->dirY = oldDirX * sin(0.02) + cube->dirY * cos(0.02);
		double oldPlaneX = cube->planeX;
		cube->planeX = cube->planeX * cos(0.02) - cube->planeY * sin(0.02);
		cube->planeY = oldPlaneX * sin(0.02) + cube->planeY * cos(0.02);
	}*/
	const float	x = cosf(cube->ray.angle) * cube->ray.move.x - \
		sinf(cube->ray.angle) * cube->ray.move.y;
	const float	y = sinf(cube->ray.angle) * cube->ray.move.x + \
		cosf(cube->ray.angle) * cube->ray.move.y;
	if (cube->pos.x + x <= cube->map->max_Y - 1 && cube->pos.x + x >= 1)
		cube->pos.x += x;
	if (cube->pos.y - y <= cube->map->max_Y - 1 && cube->pos.y - y >= 1)
		cube->pos.y += y;
	render(cube);
	return (0);
}

int	mouse_turn(int xx, int yy, t_cube *cube)
{
	(void) yy;
	static int oldx = 800 / 2;
	cube->ray.angle += (xx - oldx) * 0.001;
	oldx = xx;
/*	const float	x = cosf(cube->ray.angle) * cube->ray.move.x - \
		sinf(cube->ray.angle) * cube->ray.move.y;
	const float	y = sinf(cube->ray.angle) * cube->ray.move.x + \
		cosf(cube->ray.angle) * cube->ray.move.y;
	if (cube->pos.x + x <= cube->map->max_Y - 1 && cube->pos.x + x >= 1)
		cube->pos.x += x;
	if (cube->pos.y - y <= cube->map->max_Y - 1 && cube->pos.y - y >= 1)
		cube->pos.y += y;*/
	mlx_mouse_hide(cube->mlx, cube->win);
	mlx_mouse_move(cube->mlx, cube->win, 400, 300);
	render(cube);
	return (0);
}

int	mouse_control(int button, int x, int y, t_cube *cube)
{
	(void) button;
	(void) x;
	(void) y;
	(void) cube;
	return (0);
}
