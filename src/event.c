/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:54:00 by cassie            #+#    #+#             */
/*   Updated: 2024/05/25 15:23:39 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

int	close_window(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->img.img_ptr);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	exit(EXIT_SUCCESS);
}

int	key_control(int keycode, t_cub *cub)
{
	cub->cam.move.x = 0;
	cub->cam.move.y = 0;
	if (keycode == XK_Escape)
		close_window(cub);
	if (keycode == XK_w)
		cub->cam.move_f = true;
	if (keycode == XK_s)
		cub->cam.move_b = true;
	if (keycode == XK_a)
		cub->cam.move_l = true;
	if (keycode == XK_d)
		cub->cam.move_r = true;
	if (keycode == XK_Left)
		cub->cam.angle -= 0.05;
	if (keycode == XK_Right)
		cub->cam.angle += 0.05;
	return (0);
}

int	mouse_turn(int x, int y, t_cub *cub)
{
	(void) y;
	cub->cam.angle += (x - cub->cam.oldx) * 0.001;
	cub->cam.oldx = x;
	cub->cam.no_change = false;
	return (0);
}

int	mouse_control(int button, int x, int y, t_cub *cub)
{
	(void) button;
	(void) x;
	(void) y;
	(void) cub;
	return (0);
}

void update_cam(t_cub *cub)
{
	const float	x = cosf(cub->cam.angle) * cub->cam.move.x - \
		sinf(cub->cam.angle) * cub->cam.move.y;
	const float	y = sinf(cub->cam.angle) * cub->cam.move.x + \
		cosf(cub->cam.angle) * cub->cam.move.y;
	if (cub->ray.pos.x + x <= cub->map->max_Y - 1 && cub->ray.pos.x + x >= 1)
		cub->ray.pos.x += x;
	if (cub->ray.pos.y + y <= cub->map->max_Y - 1 && cub->ray.pos.y + y >= 1)
		cub->ray.pos.y += y;
	cub->cam.move.x = 0;
	cub->cam.move.y = 0;
}

void key_move(t_camera *cam)
{
	if (cam->move_f == true)
		cam->move.x += 0.05;
	if (cam->move_b == true)
		cam->move.x -= 0.05;
	if (cam->move_l == true)
		cam->move.y -= 0.05;
	if (cam->move_r == true)
		cam->move.y += 0.05;
	cam->no_change = false;
}

int	event_loop(t_cub *cub)
{
	key_move(&cub->cam);
	mlx_mouse_hide(cub->mlx, cub->win);
	if (cub->cam.no_change == true)
		return (0);
	cub->cam.oldx = 1920 / 2;
	mlx_mouse_move(cub->mlx, cub->win, 1920 / 2, 1080 / 2);
	update_cam(cub);
	cub->cam.no_change = true;
	render(cub);
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == XK_w)
		cub->cam.move_f = false;
	if (keycode == XK_s)
		cub->cam.move_b = false;
	if (keycode == XK_a)
		cub->cam.move_l = false;
	if (keycode == XK_d)
		cub->cam.move_r = false;
	return (0);
}
