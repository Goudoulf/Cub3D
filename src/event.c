/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:54:00 by cassie            #+#    #+#             */
/*   Updated: 2024/05/23 19:29:21 by cassie           ###   ########.fr       */
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
	if (keycode == XK_Escape)
		close_window(cube);
	if (keycode == XK_w)
	{
		check_hit_wall(cube, 0);
		// printf("max_Y=%i\n", cube->map->max_Y);
		// printf("max_X=%i\n", cube->map->max_X);
		// printf("posX=%f\n", cube->posX);
		// printf("posY=%f\n", cube->posY);
	}
	if (keycode == XK_s)
	{
		if (cube->pos.x - cube->dirX * 0.8 <= cube->map->max_Y - 1 && cube->pos.x - cube->dirX * 0.8 >= 1)
			cube->pos.x -= cube->dirX * 0.8;
		if (cube->pos.y - cube->dirY * 0.8 <= cube->map->max_X - 1 && cube->pos.y - cube->dirY * 0.8 >= 1)
			cube->pos.y -= cube->dirY * 0.8;
		printf("posX=%f\n", cube->pos.x);
		printf("posY=%f\n", cube->pos.y);
	}
	if (keycode == XK_d)
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
	}
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
