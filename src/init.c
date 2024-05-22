/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:41:08 by cassie            #+#    #+#             */
/*   Updated: 2024/05/22 15:34:05 by cassie           ###   ########.fr       */
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
	mlx_hook(cube->win, DestroyNotify, StructureNotifyMask, close_window, cube);
}

static void	data_init(t_cube *cube)
{
	cube->width = 800;
	cube->height = 600;
	cube->posX = 22, cube->posY = 12;  //x and y start position
	cube->dirX = -1, cube->dirY = 0; //initial direction vector
	cube->planeX = 0;
	cube->planeY = 0.66; //the 2d raycaster version of camera plane
}
void	init_all(t_cube *cube)
{
	cube->mlx = mlx_init();
	if (cube->mlx == NULL)
		malloc_error();
	cube->win = mlx_new_window(cube->mlx, 800, 600, "fract-ol");
	if (cube->win == NULL)
	{
		mlx_destroy_display(cube->mlx);
		free(cube->mlx);
		malloc_error();
	}
	cube->img.img_ptr = mlx_new_image(cube->mlx, 800, 600);
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
