/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 event.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: cassie <cassie@student.42lyon.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/05/21 12:54:00 by cassie			   #+#	  #+#			  */
/*	 Updated: 2024/05/28 11:49:49 by cassie			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "cub3D.h"

int	key_control(int keycode, t_cub *cub)
{
	cub->cam->move.x = 0;
	cub->cam->move.y = 0;
	if (keycode == XK_Escape)
		close_window(cub);
	if (keycode == XK_w)
		cub->cam->move_f = true;
	if (keycode == XK_s)
		cub->cam->move_b = true;
	if (keycode == XK_a)
		cub->cam->move_l = true;
	if (keycode == XK_d)
		cub->cam->move_r = true;
	if (keycode == XK_Left)
		cub->cam->cam_l = true;
	if (keycode == XK_Right)
		cub->cam->cam_r = true;
	if (keycode == XK_f && cub->door_m == true)
	{
		if (cub->map->final_map[cub->door_p.y][cub->door_p.x] == -2)
			cub->map->final_map[cub->door_p.y][cub->door_p.x] = -1;
		else if (cub->map->final_map[cub->door_p.y][cub->door_p.x] == -1)
			cub->map->final_map[cub->door_p.y][cub->door_p.x] = -2;
	}
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == XK_w)
		cub->cam->move_f = false;
	if (keycode == XK_s)
		cub->cam->move_b = false;
	if (keycode == XK_a)
		cub->cam->move_l = false;
	if (keycode == XK_d)
		cub->cam->move_r = false;
	if (keycode == XK_Left)
		cub->cam->cam_l = false;
	if (keycode == XK_Right)
		cub->cam->cam_r = false;
	return (0);
}

int	mouse_turn(int x, int y, t_cub *cub)
{
	(void) y;
	cub->cam->angle += (x - cub->cam->oldx) * 0.001;
	cub->cam->no_change = (x != cub->cam->oldx);
	cub->cam->oldx = x;
	return (0);
}

int	focus_in(t_cub *cub)
{
	cub->focus = true;
	return (0);
}

int	focus_out(t_cub *cub)
{
	cub->focus = false;
	return (0);
}

int	event_loop(t_cub *cub)
{
	key_move(cub->cam);
	mlx_mouse_hide(cub->mlx, cub->win);
	if (cub->cam->no_change == true)
		return (0);
	cub->cam->oldx = 1920 / 2;
	if (cub->focus == true)
		mlx_mouse_move(cub->mlx, cub->win, 1920 / 2, 1080 / 2);
	update_cam(cub, cub->ray, cub->map);
	check_door(cub, cub->ray, cub->map);
	render(cub);
	cub->cam->no_change = true;
	return (0);
}
