/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:43:23 by dvo               #+#    #+#             */
/*   Updated: 2024/06/01 20:14:17 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	update_cam(t_cub *cub, t_raycast *ray, t_map *map)
{
	float	x;
	float	y;

	x = cosf(cub->cam->angle) * cub->cam->move.x
		- sinf(cub->cam->angle) * cub->cam->move.y;
	y = sinf(cub->cam->angle) * cub->cam->move.x
		+ cosf(cub->cam->angle) * cub->cam->move.y;
	if (ray->pos.x + x <= map->max_x - 1 && ray->pos.x + x >= 1
		&& (map->final_map[(int)ray->pos.y][(int)(ray->pos.x + x)] == 0
		|| map->final_map[(int)ray->pos.y][(int)(ray->pos.x + x)] == -2))
		ray->pos.x += x;
	if (ray->pos.y + y <= map->max_y - 1 && ray->pos.y + y >= 1
		&& (map->final_map[(int)(ray->pos.y + y)][(int)(ray->pos.x)] == 0
		|| map->final_map[(int)(ray->pos.y + y)][(int)(ray->pos.x)] == -2))
		ray->pos.y += y;
	cub->cam->move.x = 0;
	cub->cam->move.y = 0;
}

void	set_door(t_cub *cub, bool door, int x, int y)
{
	cub->door_m = door;
	cub->door_p.y = y;
	cub->door_p.x = x;
}

void	check_door(t_cub *cub, t_raycast *ray, t_map *map)
{
	if (map->final_map[(int)(ray->pos.y + 1)][(int)(ray->pos.x)] == -1
		|| map->final_map[(int)(ray->pos.y + 1)][(int)(ray->pos.x)] == -2)
		return (set_door(cub, true, ray->pos.x, ray->pos.y + 1));
	if (map->final_map[(int)(ray->pos.y - 1)][(int)(ray->pos.x)] == -1
		|| map->final_map[(int)(ray->pos.y - 1)][(int)(ray->pos.x)] == -2)
		return (set_door(cub, true, ray->pos.x, ray->pos.y - 1));
	if (map->final_map[(int)(ray->pos.y)][(int)(ray->pos.x) - 1] == -1
		|| map->final_map[(int)(ray->pos.y)][(int)(ray->pos.x) - 1] == -2)
		return (set_door(cub, true, ray->pos.x - 1, ray->pos.y));
	if (map->final_map[(int)(ray->pos.y)][(int)(ray->pos.x) + 1] == -1
		|| map->final_map[(int)(ray->pos.y)][(int)(ray->pos.x) + 1] == -2)
		return (set_door(cub, true, ray->pos.x + 1, ray->pos.y));
	set_door(cub, false, 0, 0);
}

void	key_move(t_camera *cam)
{
	if (cam->move_f == true)
		cam->move.x += 0.05;
	if (cam->move_b == true)
		cam->move.x -= 0.05;
	if (cam->move_l == true)
		cam->move.y -= 0.05;
	if (cam->move_r == true)
		cam->move.y += 0.05;
	if (cam->cam_l == true)
		cam->angle -= 0.02;
	if (cam->cam_r == true)
		cam->angle += 0.02;
	cam->no_change = false;
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
