/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:43:23 by dvo               #+#    #+#             */
/*   Updated: 2024/05/23 14:16:10 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>
#include <stdio.h>


void	limit_move_wall(t_cube *cube)
{
	int	x;
	int	y;

	x = (int) (cube->posX + cube->dirX);
	y = (int) (cube->posY + cube->dirY * 0.1);
	if (cube->map->final_map[y][x] == 0)
	{
		cube->posY += cube->dirY * 0.1;
		if (cube->dirX >= 0)
			cube->posX = x + 1 - 0.00001;
		else
			cube->posX= x + 0.00001;
		return ;
	}
}

void	check_hit_wall(t_cube *cube, int i)
{
	int	x;
	int	y;

    if (i == 1)
    {
        //check_backward_wall(cube);
        return ;
    }
	x = (int) (cube->posX + cube->dirX * 0.1);
	y = (int) (cube->posY + cube->dirY * 0.1);
	printf("\n\nMAP at %i, %i is: %i\n", y, x, cube->map->final_map[y][x]);
	if (cube->map->final_map[y][x] == 0)
	{
		printf("NO WALL\n");
		cube->posX += cube->dirX * 0.1;
		cube->posY += cube->dirY * 0.1;
		return ;
	}
	y = (int) (cube->posY + cube->dirY);
	if (cube->map->final_map[y][x] == 0)
	{
		cube->posX += cube->dirX * 0.1;
		if (cube->dirY >= 0)
			cube->posY = y + 1 - 0.00001;
		else
			cube->posY= y + 0.00001;
		return ;
	}
	limit_move_wall(cube);
}
