/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   init.c						:+:	 :+:	:+:   */
/*						      +:+ +:+	      +:+     */
/*   By: cassie <cassie@student.42lyon.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/05/21 12:41:08 by cassie	       #+#    #+#	      */
/*   Updated: 2024/05/28 11:40:02 by cassie	      ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "cub3D.h"
#include <X11/X.h>
#include <stdio.h>

static void	malloc_error(t_cub *cub)
{
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->img.img_ptr)
		mlx_destroy_image(cub->mlx, cub->img.img_ptr);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	free(cub);
	exit(EXIT_FAILURE);
}

static void	event_init(t_cub *cub)
{
	mlx_hook(cub->win, KeyPress, KeyPressMask, key_control, cub);
	mlx_hook(cub->win, KeyRelease, KeyReleaseMask, key_release, cub);
	mlx_hook(cub->win, MotionNotify, PointerMotionMask, mouse_turn, cub);
	mlx_hook(cub->win, DestroyNotify, StructureNotifyMask, close_window, cub);
	mlx_hook(cub->win, FocusIn, FocusChangeMask, focus_in, cub);
	mlx_hook(cub->win, FocusOut, FocusChangeMask, focus_out, cub);
	mlx_loop_hook(cub->mlx, event_loop, cub);
}

float	set_angle(t_cub *cub)
{
	float	ret;

	ret = 0;
	if (cub->init_view == 'N')
		ret = -M_PI / 2;
	if (cub->init_view == 'S')
		ret = M_PI / 2;
	if (cub->init_view == 'E')
		ret = M_PI;
	if (cub->init_view == 'W')
		ret = -M_PI;
	return (ret);
}

static int	cub_init(t_cub *cub)
{
	cub->texture.move = NULL;
	cub->door_m = false;
	cub->ray = ft_calloc(1, sizeof(t_raycast));
	if (!cub->ray)
		return (-1);
	cub->cam = ft_calloc(1, sizeof(t_camera));
	if (!cub->cam)
	{
		free (cub->ray);
		return (-1);
	}
	cub->cam->width = WIDTH;
	cub->cam->height = HEIGHT;
	cub->cam->oldx = cub->cam->width / 2;
	cub->cam->angle = 0;
	cub->cam->move_f = false;
	cub->cam->move_b = false;
	cub->cam->move_l = false;
	cub->cam->move_r = false;
	cub->cam->fov = 90;
	cub->cam->fov_rad = cub->cam->fov * M_PI * 0.5 / 180.0;
	cub->win_x = WIDTH;
	cub->win_y = HEIGHT;
	cub->mini_map.last_pos.x = cub->ray->pos.x;
	cub->mini_map.last_pos.y = cub->ray->pos.y;
	return (0);
}

void	init_all(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (cub->mlx == NULL)
		malloc_error(cub);
	cub->win = mlx_new_window(cub->mlx, 1920, 1080, "cub3D");
	if (cub->win == NULL)
		malloc_error(cub);
	cub->img.img_ptr = mlx_new_image(cub->mlx, 1920, 1080);
	if (cub->img.img_ptr == NULL)
		malloc_error(cub);
	cub->img.buffer = mlx_get_data_addr(cub->img.img_ptr,
			&cub->img.bpp, &cub->img.line_len, &cub->img.endian);
	event_init(cub);
	if (cub_init(cub) == -1)
		malloc_error(cub);
}
