/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:43:23 by dvo               #+#    #+#             */
/*   Updated: 2024/06/03 07:03:35 by cassie           ###   ########.fr       */
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
		cam->angle -= 0.04;
	if (cam->cam_r == true)
		cam->angle += 0.04;
	cam->no_change = false;
}

int	event_loop(t_cub *cub)
{
	key_move(cub->cam);
	mlx_mouse_hide(cub->mlx, cub->win);
	if (cub->cam->no_change == true)
		return (0);
	if (cub->focus == true)
		mlx_mouse_move(cub->mlx, cub->win, 1920 / 2, 1080 / 2);
	update_cam(cub, cub->ray, cub->map);
	render(cub);
	cub->cam->no_change = true;
	return (0);
}
