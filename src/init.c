/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:12:06 by cassie            #+#    #+#             */
/*   Updated: 2024/06/01 14:50:43 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	event_init(t_cub *cub)
{
	mlx_hook(cub->win, KeyPress, KeyPressMask, key_control, cub);
	mlx_hook(cub->win, KeyRelease, KeyReleaseMask, key_release, cub);
	mlx_hook(cub->win, DestroyNotify, StructureNotifyMask, close_window, cub);
	mlx_hook(cub->win, FocusIn, FocusChangeMask, focus_in, cub);
	mlx_hook(cub->win, FocusOut, FocusChangeMask, focus_out, cub);
	mlx_loop_hook(cub->mlx, event_loop, cub);
}

static int	cub_init(t_cub *cub)
{
	cub->ray = ft_calloc(1, sizeof(t_raycast));
	if (!cub->ray)
		malloc_error(cub, true);
	cub->cam = ft_calloc(1, sizeof(t_camera));
	if (!cub->cam)
		malloc_error(cub, true);
	cub->cam->width = WIDTH;
	cub->cam->height = HEIGHT;
	cub->cam->angle = 0;
	cub->cam->move_f = false;
	cub->cam->move_b = false;
	cub->cam->move_l = false;
	cub->cam->move_r = false;
	cub->cam->fov = 90;
	cub->cam->fov_rad = cub->cam->fov * M_PI * 0.5 / 180.0;
	cub->win_x = WIDTH;
	cub->win_y = HEIGHT;
	return (0);
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

void	init_all(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (cub->mlx == NULL)
		malloc_error(cub, true);
	cub->win = mlx_new_window(cub->mlx, 1920, 1080, "cub3D");
	if (cub->win == NULL)
		malloc_error(cub, true);
	cub->img.img_ptr = mlx_new_image(cub->mlx, 1920, 1080);
	if (cub->img.img_ptr == NULL)
		malloc_error(cub, true);
	cub->img.buffer = mlx_get_data_addr(cub->img.img_ptr,
			&cub->img.bpp, &cub->img.line_len, &cub->img.endian);
	event_init(cub);
	if (cub_init(cub) == -1)
		malloc_error(cub, true);
}
