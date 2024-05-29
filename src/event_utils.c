/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:43:23 by dvo               #+#    #+#             */
/*   Updated: 2024/05/29 20:43:05 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update_cam(t_cub *cub, t_raycast *ray, t_map *map)
{
	float	x;
	float	y;

	x = cosf(cub->cam->angle) * cub->cam->move.x
		- sinf(cub->cam->angle) * cub->cam->move.y;
	y = sinf(cub->cam->angle) * cub->cam->move.x
		+ cosf(cub->cam->angle) * cub->cam->move.y;
	if (ray->pos.x + x <= map->max_X - 1 && ray->pos.x + x >= 1
		&& (map->final_map[(int)ray->pos.y][(int)(ray->pos.x + x)] == 0
		|| map->final_map[(int)ray->pos.y][(int)(ray->pos.x + x)] == -2))
		ray->pos.x += x;
	if (ray->pos.y + y <= map->max_Y - 1 && ray->pos.y + y >= 1
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
