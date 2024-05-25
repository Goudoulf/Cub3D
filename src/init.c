/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:41:08 by cassie            #+#    #+#             */
/*   Updated: 2024/05/25 19:37:01 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <X11/X.h>

static void	malloc_error(void)
{
	exit(EXIT_FAILURE);
}

static void	event_init(t_cub *cub)
{
	mlx_hook(cub->win, KeyPress, KeyPressMask, key_control, cub);
	mlx_hook(cub->win, KeyRelease, KeyReleaseMask, key_release, cub);
	mlx_hook(cub->win, ButtonPress, ButtonPressMask, mouse_control, cub);
	mlx_hook(cub->win, MotionNotify, PointerMotionMask, mouse_turn, cub);
	mlx_hook(cub->win, DestroyNotify, StructureNotifyMask, close_window, cub);
	mlx_loop_hook(cub->mlx, event_loop, cub);
}

static void	data_init(t_cub *cub)
{
	cub->cam.width = WIDTH;
	cub->cam.height = HEIGHT;
	cub->cam.oldx = cub->cam.width / 2;
	cub->ray.pos.x = 0;
	cub->ray.pos.y = 0;
//	cub->dirX = -1, cub->dirY = 0; //initial direction vector
//	cub->planeX = 0;
//	cub->planeY = 0.66; //the 2d raycaster version of camera plane
	cub->ray.hit = 0;
	cub->ray.map.x = 0;
	cub->ray.map.y = 0;
	cub->ray.side = 0;
	cub->ray.color = 0;
	cub->ray.step.x = 0;
	cub->ray.step.y = 0;
	cub->ray.cameraX = 0;
	cub->ray.drawEnd = 0;
	cub->ray.rayDir.x = 0;
	cub->ray.rayDir.y = 0;
	cub->ray.drawStart = 0;
	cub->ray.sideDist.x = 0;
	cub->ray.sideDist.y = 0;
	cub->ray.deltaDist.x = 0;
	cub->ray.deltaDist.y = 0;
	cub->ray.lineHeight = 0;
	cub->ray.perpWallDist = 0;
	cub->cam.angle = M_PI;
	cub->cam.move_f = false;
	cub->cam.move_b = false;
	cub->cam.move_l = false;
	cub->cam.move_r = false;
	cub->cam.fov = 90;
	cub->cam.fov_rad = cub->cam.fov * M_PI * 0.5 / 180.0;
	cub->win_x = WIDTH;
	cub->win_y = HEIGHT;
	cub->mini_map.last_pos.x = cub->ray.pos.x;
	cub->mini_map.last_pos.y = cub->ray.pos.y;
}

void	texture_init(t_cub *cub)
{
	cub->texture.north.img_ptr = mlx_xpm_file_to_image(cub->mlx, "./textures/mossy.xpm", &cub->texture.north.width, &cub->texture.north.height);	
	if (!cub->texture.north.img_ptr)
		exit(1);
	cub->texture.north.buffer = mlx_get_data_addr(cub->texture.north.img_ptr,
			&cub->texture.north.bpp, &cub->texture.north.line_len, &cub->texture.north.endian);
	cub->texture.south.img_ptr = mlx_xpm_file_to_image(cub->mlx, "./textures/greystone.xpm",&cub->texture.south.width, &cub->texture.south.height); 
	if (!cub->texture.south.img_ptr)
		exit(1);
	cub->texture.south.buffer = mlx_get_data_addr(cub->texture.south.img_ptr,
			&cub->texture.south.bpp, &cub->texture.south.line_len, &cub->texture.south.endian);
}

void	init_all(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (cub->mlx == NULL)
		malloc_error();
	cub->win = mlx_new_window(cub->mlx, 1920, 1080, "Cub3D");
	if (cub->win == NULL)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		malloc_error();
	}
	cub->img.img_ptr = mlx_new_image(cub->mlx, 1920, 1080);
	if (cub->img.img_ptr == NULL)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		malloc_error();
	}
	cub->img.buffer = mlx_get_data_addr(cub->img.img_ptr,
			&cub->img.bpp, &cub->img.line_len, &cub->img.endian);
	event_init(cub);
	data_init(cub);
	texture_init(cub);
}
