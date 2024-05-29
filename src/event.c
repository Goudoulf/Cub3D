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
#include <math.h>

int	close_window(t_cub *cub)
{
	int i = -1;
	mlx_destroy_image(cub->mlx, cub->texture.north.img_ptr);
	mlx_destroy_image(cub->mlx, cub->texture.south.img_ptr);
	mlx_destroy_image(cub->mlx, cub->texture.statue.img_ptr);
	mlx_destroy_image(cub->mlx, cub->texture.scream.img_ptr);
	mlx_destroy_image(cub->mlx, cub->mini_map.img.img_ptr);
	mlx_destroy_image(cub->mlx, cub->mini_map.img_pos.img_ptr);
	mlx_destroy_image(cub->mlx, cub->img.img_ptr);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	while (cub->map->map[++i])
		free(cub->map->map[i]);
	free(cub->map->map);
	i = -1;
	while (++i < cub->map->max_Y)
		free(cub->map->final_map[i]);
	free(cub->map->final_map);
	i = -1;
	while (cub->map->buffer[++i])
		free(cub->map->buffer[i]);
	free(cub->map->buffer);
	free(cub->map->north);
	free(cub->map->south);
	free(cub->map->east);
	free(cub->map->west);
	free(cub->map);
	free(cub->mlx);
	free(cub->ray);
	free(cub->cam);
	free(cub);
	exit(EXIT_SUCCESS);
}

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
		cub->cam->angle -= 0.05;
	if (keycode == XK_Right)
		cub->cam->angle += 0.05;
	if (keycode == XK_f &&  cub->door_m == true)
	{		
		if (cub->map->final_map[cub->door_p.y][cub->door_p.x] == -2)
			cub->map->final_map[cub->door_p.y][cub->door_p.x] = -1;
		else if (cub->map->final_map[cub->door_p.y][cub->door_p.x] == -1)
			cub->map->final_map[cub->door_p.y][cub->door_p.x] = -2;
	}
	return (0);
}

int	mouse_turn(int x, int y, t_cub *cub)
{
	(void) y;
	cub->cam->angle += (x - cub->cam->oldx) * 0.001;
	cub->cam->oldx = x;
	cub->cam->no_change = false;
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
	const float	x = cosf(cub->cam->angle) * cub->cam->move.x - \
		sinf(cub->cam->angle) * cub->cam->move.y;
	const float	y = sinf(cub->cam->angle) * cub->cam->move.x + \
		cosf(cub->cam->angle) * cub->cam->move.y;
	if (cub->ray->pos.x + x <= cub->map->max_X - 1 && cub->ray->pos.x + x >= 1 
		&& (cub->map->final_map[(int)cub->ray->pos.y][(int)(cub->ray->pos.x + x)] == 0
		|| cub->map->final_map[(int)cub->ray->pos.y][(int)(cub->ray->pos.x + x)] == -2))
		cub->ray->pos.x += x;
	if (cub->ray->pos.y + y <= cub->map->max_Y - 1 && cub->ray->pos.y + y >= 1
		&& (cub->map->final_map[(int)(cub->ray->pos.y + y)][(int)(cub->ray->pos.x)] == 0
		|| cub->map->final_map[(int)(cub->ray->pos.y + y)][(int)(cub->ray->pos.x)] == -2))
		cub->ray->pos.y += y;
	cub->cam->move.x = 0;
	cub->cam->move.y = 0;
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

void check_door(t_cub *cub)
{
	if (cub->map->final_map[(int)(cub->ray->pos.y + 1)][(int)(cub->ray->pos.x)] == -1 
		|| cub->map->final_map[(int)(cub->ray->pos.y + 1)][(int)(cub->ray->pos.x)] == -2)
	{
		cub->door_m = true;
		cub->door_p.y = cub->ray->pos.y + 1;
		cub->door_p.x = cub->ray->pos.x;
		return ;
	}
	if (cub->map->final_map[(int)(cub->ray->pos.y - 1)][(int)(cub->ray->pos.x)] == -1
		|| cub->map->final_map[(int)(cub->ray->pos.y - 1)][(int)(cub->ray->pos.x)] == -2)
	{
		cub->door_m = true;
		cub->door_p.y = cub->ray->pos.y - 1;
		cub->door_p.x = cub->ray->pos.x;
		return ;
	}
	if (cub->map->final_map[(int)(cub->ray->pos.y)][(int)(cub->ray->pos.x) - 1] == -1
		|| cub->map->final_map[(int)(cub->ray->pos.y)][(int)(cub->ray->pos.x) - 1] == -2)
	{
		cub->door_m = true;
		cub->door_p.y = cub->ray->pos.y;
		cub->door_p.x = cub->ray->pos.x - 1;
		return ;
	}
	if (cub->map->final_map[(int)(cub->ray->pos.y)][(int)(cub->ray->pos.x) + 1] == -1 
		|| cub->map->final_map[(int)(cub->ray->pos.y)][(int)(cub->ray->pos.x) + 1] == -2)
	{
		cub->door_m = true;
		cub->door_p.y = cub->ray->pos.y;
		cub->door_p.x = cub->ray->pos.x + 1;
		return ;
	}
	cub->door_m = false;
	cub->door_p.y = 0;
	cub->door_p.x = 0;
}

int	event_loop(t_cub *cub)
{
	key_move(cub->cam);
	mlx_mouse_hide(cub->mlx, cub->win);
	if (cub->cam->no_change == true)
		return (0);
	cub->cam->oldx = 1920 / 2;
	mlx_mouse_move(cub->mlx, cub->win, 1920 / 2, 1080 / 2);
	update_cam(cub);
	check_door(cub);
//	if (cub->door_m == true)
//		printf("door waiting\n");
	cub->cam->no_change = true;
	render(cub);
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
	return (0);
}
