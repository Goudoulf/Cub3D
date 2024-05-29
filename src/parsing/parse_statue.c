/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parse_statue.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dvo <dvo@student.42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/05/28 10:54:20 by dvo			   #+#	  #+#			  */
/*	 Updated: 2024/05/29 14:02:11 by cassie			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "cub3D.h"

int	check_road(int **map, int posy, int posx, t_cub *cub);

void	ft_add_ennemy(t_cub *cub)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (y < cub->map->max_Y)
	{
		while (x < cub->map->max_X)
		{
			if (cub->map->final_map[y][x] == 0
				&& check_road(cub->map->final_map, y, x, cub))
			{
				cub->map->final_map[y][x] = 2;
				cub->posX_ennemy = x;
				cub->posY_ennemy = y;
				return ;
			}
			x++;
		}
		y++;
		x = 0;
	}
}

static int	check_around(int **map, int y, int x, t_cub *cub)
{
	int	nbr;

	nbr = 0;
	if (x > 0 && map[y][x - 1] == 0)
	{
		map[y][x - 1] = 5;
		nbr++;
	}
	if (x < cub->map->max_X && map[y][x + 1] == 0)
	{
		map[y][x + 1] = 5;
		nbr++;
	}
	if (y < cub->map->max_Y && map[y + 1][x] == 0)
	{
		map[y + 1][x] = 5;
		nbr++;
	}
	if (y > 0 && map[y - 1][x] == 0)
	{
		map[y - 1][x] = 5;
		nbr++;
	}
	return (nbr);
}

int	reset_five(int **map, t_cub *cub)
{
	int	res;
	int	y;
	int	x;

	res = 0;
	y = 0;
	if (map[(int)cub->ray->pos.y][(int)cub->ray->pos.x] == 5)
		res = 1;
	while (y < cub->map->max_Y)
	{
		x = 0;
		while (x < cub->map->max_X)
		{
			if (map[y][x] == 5)
				map[y][x] = 0;
			x++;
		}
		y++;
	}
	return (res);
}

int	check_road(int **map, int posy, int posx, t_cub *cub)
{
	int	nbr_five;
	int	x;
	int	y;

	nbr_five = 1;
	y = 0;
	map[posy][posx] = 5;
	while (nbr_five != 0)
	{
		nbr_five = 0;
		while (y < cub->map->max_Y)
		{
			x = 0;
			while (x < cub->map->max_X)
			{
				if (map[y][x] == 5)
					nbr_five += check_around(map, y, x, cub);
				x++;
			}
			y++;
		}
	}
	return (reset_five(map, cub));
}
