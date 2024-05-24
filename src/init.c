/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:41:08 by cassie            #+#    #+#             */
/*   Updated: 2024/05/24 13:53:54 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	malloc_error(void)
{
	exit(EXIT_FAILURE);
}

static void	event_init(t_cube *cube)
{
	mlx_hook(cube->win, KeyPress, KeyPressMask, key_control, cube);
	mlx_hook(cube->win, ButtonPress, ButtonPressMask, mouse_control, cube);
	mlx_hook(cube->win, 6, PointerMotionMask, mouse_camera, cube);
	mlx_hook(cube->win, DestroyNotify, StructureNotifyMask, close_window, cube);
}

static void	data_init(t_cube *cube)
{
	cube->width = cube->win_x;
	cube->height = cube->win_y;
	cube->dirX = -1, cube->dirY = 0; //initial direction vector
	cube->planeX = 0;
	cube->planeY = 0.66; //the 2d raycaster version of camera plane
	cube->ray.hit = 0;
	cube->ray.mapX = 0;
	cube->ray.mapY = 0;
	cube->ray.side = 0;
	cube->ray.color = 0;
	cube->ray.stepX = 0;
	cube->ray.stepY = 0;
	cube->ray.cameraX = 0;
	cube->ray.drawEnd = 0;
	cube->ray.rayDirX = 0;
	cube->ray.rayDirY = 0;
	cube->ray.drawStart = 0;
	cube->ray.sideDistX = 0;
	cube->ray.sideDistY = 0;
	cube->ray.deltaDistX = 0;
	cube->ray.deltaDistY = 0;
	cube->ray.lineHeight = 0;
	cube->ray.perpWallDist = 0;
}


void	init_all(t_cube *cube)
{
	cube->win_x = 800;
	cube->win_y = 600;
	cube->mlx = mlx_init();
	if (cube->mlx == NULL)
		malloc_error();
	cube->win = mlx_new_window(cube->mlx, cube->win_x, cube->win_y, "Cub3D");
	if (cube->win == NULL)
	{
		mlx_destroy_display(cube->mlx);
		free(cube->mlx);
		malloc_error();
	}
	cube->img.img_ptr = mlx_new_image(cube->mlx, cube->win_x, cube->win_y);
	if (cube->img.img_ptr == NULL)
	{
		mlx_destroy_window(cube->mlx, cube->win);
		mlx_destroy_display(cube->mlx);
		free(cube->mlx);
		malloc_error();
	}
	cube->img.buffer = mlx_get_data_addr(cube->img.img_ptr,
			&cube->img.bpp, &cube->img.line_len, &cube->img.endian);
	event_init(cube);
	data_init(cube);
}
