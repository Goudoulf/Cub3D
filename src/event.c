/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:54:00 by cassie            #+#    #+#             */
/*   Updated: 2024/05/23 11:09:02 by dvo              ###   ########.fr       */
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

int	check_hit_wall(double new_posX, double new_posY, t_cube *cube)
{
	if ()
	return (0);
}

int	key_control(int keycode, t_cube *cube)
{
	if (keycode == XK_Escape)
		close_window(cube);
	if (keycode == XK_w)
	{
		// if (!check_hit_wall(cube->posX + cube->dirX * 1.02, cube->posY + cube->dirY * 1.02, cube))
		// {
		// 	cube->posX += cube->dirX * 1.02;
		// 	cube->posY += cube->dirY * 1.02;
		// }
		if (cube->posX + cube->dirX * 1.02 < cube->map->max_X && cube->posX + cube->dirX * 1.02 > 0)
			cube->posX += cube->dirX * 1.02;
		if (cube->posY + cube->dirY * 1.02 < cube->map->max_Y && cube->posY + cube->dirY * 1.02 > 0)
			cube->posY += cube->dirY * 1.02;
		printf("posX=%f vs maxX=%i\n", cube->posX, cube->map->max_X);
		printf("posY=%f vs maxY=%i\n", cube->posY, cube->map->max_Y);
	}
	if (keycode == XK_s)
	{
		if (cube->posX - cube->dirX * 1.02 < cube->map->max_Y && cube->posX - cube->dirX * 1.02 > 0)
			cube->posX -= cube->dirX * 1.02;
		if (cube->posY - cube->dirY * 1.02 < cube->map->max_X && cube->posY - cube->dirY * 1.02 > 0)
			cube->posY -= cube->dirY * 1.02;
		printf("posX=%f vs maxX=%i\n", cube->posX, cube->map->max_X);
		printf("posY=%f vs maxY=%i\n", cube->posY, cube->map->max_Y);
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
	raycast(cube);
	return (0);
}

int	mouse_control(int button, int x, int y, t_cube *cube)
{
	(void) button;
	(void) x;
	(void)y;
	(void) cube;
	return (0);
}
