/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:41:08 by cassie            #+#    #+#             */
/*   Updated: 2024/05/21 13:50:03 by dvo              ###   ########.fr       */
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
}
void	init_all(t_cube *cube)
{
	cube->mlx = mlx_init();
	if (cube->mlx == NULL)
		malloc_error();
	cube->win = mlx_new_window(cube->mlx, 800, 600, "Cub3D");
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
