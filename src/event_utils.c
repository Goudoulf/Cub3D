/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:43:23 by dvo               #+#    #+#             */
/*   Updated: 2024/05/25 09:56:02 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>
#include <stdio.h>

/*
void	limit_move_wall(t_cub *cub)
{
	int	x;
	int	y;

	x = (int) (cub->pos.x + cub->dirX);
	y = (int) (cub->pos.y + cub->dirY * 0.1);
	if (cub->map->final_map[y][x] == 0)
	{
		cub->pos.y += cub->dirY * 0.1;
		if (cub->dirX >= 0)
			cub->pos.x = x + 1 - 0.00001;
		else
			cub->pos.x= x + 0.00001;
		return ;
	}
}*/
/*
void	check_hit_wall(t_cub *cub, int i)
{
	int	x;
	int	y;

    if (i == 1)
    {
        //check_backward_wall(cub);
        return ;
    }
	x = (int) (cub->pos.x + cub->dirX * 0.1);
	y = (int) (cub->pos.y + cub->dirY * 0.1);
	printf("\n\nMAP at %i, %i is: %i\n", y, x, cub->map->final_map[y][x]);
	if (cub->map->final_map[y][x] == 0)
	{
		printf("NO WALL\n");
		cub->pos.x += cub->dirX * 0.1;
		cub->pos.y += cub->dirY * 0.1;
		return ;
	}
	y = (int) (cub->pos.y + cub->dirY);
	if (cub->map->final_map[y][x] == 0)
	{
		cub->pos.x += cub->dirX * 0.1;
		if (cub->dirY >= 0)
			cub->pos.y = y + 1 - 0.00001;
		else
			cub->pos.y= y + 0.00001;
		return ;
	}
	limit_move_wall(cub);
}*/
