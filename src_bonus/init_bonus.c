/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:12:06 by cassie            #+#    #+#             */
/*   Updated: 2024/06/03 13:05:19 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
		ret = 0;
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
		malloc_error(cub, true);
	cub->cam = ft_calloc(1, sizeof(t_camera));
	if (!cub->cam)
		malloc_error(cub, true);
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
