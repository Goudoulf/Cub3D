/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:41:08 by cassie            #+#    #+#             */
/*   Updated: 2024/05/24 21:12:42 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <X11/X.h>

static void	malloc_error(void)
{
	exit(EXIT_FAILURE);
}

static void	event_init(t_cube *cube)
{
	mlx_hook(cube->win, KeyPress, KeyPressMask, key_control, cube);
	mlx_hook(cube->win, KeyRelease, KeyReleaseMask, key_release, cube);
	mlx_hook(cube->win, ButtonPress, ButtonPressMask, mouse_control, cube);
	mlx_hook(cube->win, MotionNotify, PointerMotionMask, mouse_turn, cube);
	mlx_hook(cube->win, DestroyNotify, StructureNotifyMask, close_window, cube);
	mlx_loop_hook(cube->mlx, event_loop, cube);
}

static void	data_init(t_cube *cube)
{
	cube->width = 800;
	cube->height = 600;
	cube->oldx = 800 / 2;
	cube->pos.x = cube->map->player->init_player_x, cube->pos.y = cube->map->player->init_player_y;  //x and y start position
	cube->dirX = -1, cube->dirY = 0; //initial direction vector
	cube->planeX = 0;
	cube->planeY = 0.66; //the 2d raycaster version of camera plane
	cube->ray.hit = 0;
	cube->ray.map.x = 0;
	cube->ray.map.y = 0;
	cube->ray.side = 0;
	cube->ray.color = 0;
	cube->ray.step.x = 0;
	cube->ray.step.y = 0;
	cube->ray.cameraX = 0;
	cube->ray.drawEnd = 0;
	cube->ray.rayDir.x = 0;
	cube->ray.rayDir.y = 0;
	cube->ray.drawStart = 0;
	cube->ray.sideDist.x = 0;
	cube->ray.sideDist.y = 0;
	cube->ray.deltaDist.x = 0;
	cube->ray.deltaDist.y = 0;
	cube->ray.lineHeight = 0;
	cube->ray.perpWallDist = 0;
	cube->ray.angle = M_PI;
	cube->ray.move_f = false;
	cube->ray.move_b = false;
	cube->ray.move_l = false;
	cube->ray.move_r = false;
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
