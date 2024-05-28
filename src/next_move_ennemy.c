/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_move_ennemy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:29:01 by dvo               #+#    #+#             */
/*   Updated: 2024/05/28 15:30:23 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void change_pos_statue(t_cub *cub, int x, int y)
{
    if ((int)cub->posX_ennemy > x)
		cub->posX_ennemy -= 0.05;
    else if ((int)cub->posX_ennemy < x)
	    cub->posX_ennemy += 0.05;
    else if ((int)cub->posY_ennemy > y)
	    cub->posY_ennemy -= 0.05;
    else if ((int)cub->posY_ennemy < y)
	    cub->posY_ennemy += 0.05;
    cub->map->final_map[(int)cub->posY_ennemy][(int)cub->posX_ennemy] = 2;
    if ((int)cub->posY_ennemy == (int)(cub->ray->pos.y) && (int)(cub->posX_ennemy) == (int)(cub->ray->pos.x))
        cub->flag_die = 1;
}

static void add_distance(t_cub *cub, int y, int x, int dist)
{
	if (x > 0 && cub->map->final_map[y][x - 1] == 0)
		cub->map->final_map[y][x - 1] = dist;
	if (x < cub->map->max_X && cub->map->final_map[y][x + 1] == 0)
		cub->map->final_map[y][x + 1] = dist;
	if (y < cub->map->max_Y && cub->map->final_map[y + 1][x] == 0)
		cub->map->final_map[y + 1][x] = dist;
	if (y > 0 && cub->map->final_map[y - 1][x] == 0)
		cub->map->final_map[y - 1][x] = dist;
}

static void reset_map(int **map, t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y < cub->map->max_Y)
		{
			x = 0;
			while (x < cub->map->max_X)
			{
				if (map[y][x] > 1)
					map[y][x] = 0;
				x++;
			}
			y++;
		}
}

static void	move_vector(t_cub *cub, int **map)
{
	int	dist;
	int	x;
	int	y;

	dist = map[(int)cub->ray->pos.y][(int)cub->ray->pos.x];
	x = (int)cub->ray->pos.x;
	y = (int)cub->ray->pos.y;
	while (dist > 3)
	{
		if (x > 0 && cub->map->final_map[y][x - 1] == dist - 1)
			x -= 1;
		else if (x < cub->map->max_X && cub->map->final_map[y][x + 1] == dist - 1)
			x += 1;
		else if (y < cub->map->max_Y && cub->map->final_map[y + 1][x] == dist - 1)
			y += 1;
		else if (y > 0 && cub->map->final_map[y - 1][x] == dist - 1)
			y -= 1;
		dist--;
	}
	reset_map(map, cub);
	change_pos_statue(cub, x, y);
}

void	ft_sonar(t_cub *cub, int **map)
{
	int	dist;
	int	x;
	int	y;

	dist = 2;
	y = 0;
	while (map[(int)cub->ray->pos.y][(int)cub->ray->pos.x] == 0)
	{
		while (y < cub->map->max_Y)
		{
			x = 0;
			while (x < cub->map->max_X)
			{
				if (map[y][x] == dist)
					add_distance(cub, y, x, dist + 1);
				x++;
			}
			y++;
		}
		dist++;
		y = 0;
	}
	move_vector(cub, map);
}
