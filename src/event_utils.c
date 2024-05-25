/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:43:23 by dvo               #+#    #+#             */
/*   Updated: 2024/05/24 19:00:45 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>
#include <stdio.h>

void	check_hit_wall(t_cube *cube, double ms, int i)
{
	int	x;
	int	y;

	x = (int) (cube->posX + cube->dirX * (ms + 0.05) * i );
	y = (int) (cube->posY + cube->dirY * (ms + 0.05) * i );
	if (cube->map->final_map[y][x] == 0)
	{
		cube->posX = cube->posX + cube->dirX * ms * i;
		cube->posY = cube->posY + cube->dirY * ms * i;
		return ;
	}
	y = (int) (cube->posY + cube->dirY * i);
	if (cube->map->final_map[y][x] == 0)
	{
		cube->posX = cube->posX + cube->dirX * ms * i;
		return ;
	}
	x = (int) (cube->posX + cube->dirX * i);
	y = (int) (cube->posY + cube->dirY * ms * i);
	if (cube->map->final_map[y][x] == 0)
		cube->posY = cube->posY + cube->dirY * ms * i;
}
