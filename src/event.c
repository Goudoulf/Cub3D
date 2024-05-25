/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:54:00 by cassie            #+#    #+#             */
/*   Updated: 2024/05/24 16:48:04 by dvo              ###   ########.fr       */
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
	double	ms;

	ms = 0.3;
	ft_reset_pos_minimap(cube);
	if (keycode == XK_Escape)
		close_window(cube);
	if (keycode == XK_w)
	{
		check_hit_wall(cube, ms, 1);
	}
	if (keycode == XK_s)
	{
		check_hit_wall(cube, ms, -1);
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

int	mouse_camera(int x, int y, t_cube *cube)
{
	(void)y;
	double	new_x;

	new_x = -1 * ((cube->win_x / 2) - x) / (cube->win_x / 20);

	if (!new_x)
		return (0);
	double oldDirX = cube->dirX;
	cube->dirX = cube->dirX * cos(new_x * -0.02) - cube->dirY * sin(new_x * -0.02);
	cube->dirY = oldDirX * sin(new_x * -0.02) + cube->dirY * cos(new_x * -0.02);
	double oldPlaneX = cube->planeX;
	cube->planeX = cube->planeX * cos(new_x * -0.02) - cube->planeY * sin(new_x * -0.02);
	cube->planeY = oldPlaneX * sin(new_x * -0.02) + cube->planeY * cos(new_x * -0.02);
	mlx_mouse_move(cube->mlx ,cube->win, 400, 300);
	render(cube);
	return (0);
}
