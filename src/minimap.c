/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:11:16 by dvo               #+#    #+#             */
/*   Updated: 2024/05/24 16:49:22 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int ft_border(t_cube *cube, int x, int y)
{
	if (x > (cube->win_x / 3) - 5 || x < 5)
		return (1);
	if (y > (cube->win_y / 3) - 5 || y < 5)
		return (1);
	return (0);
}

int ft_check_wall(t_cube *cube, int x, int y)
{
	int posx;
	int posy;

	posx = (cube->map->max_X * x) / (cube->win_x / 3);
	posy = (cube->map->max_Y * y) / (cube->win_y / 3);
	if (cube->map->final_map[posy][posx] == 1)
		return (1);
	return (0);
}

void	ft_set_minimap(t_cube *cube)
{
	int offset;
	int	x;
	int	y;

	x = 0;
	y = 0;

	int wall = (0 << 16) | (255 << 8) | 0;
	int border = (218 << 16) | (165 << 8) | 32;
	while (y < cube->win_y / 3)	
	{
		while(x < cube->win_x / 3)
		{
			offset = (cube->mini_map.line_len * y) + (x * (cube->mini_map.bpp / 8));
			if (ft_border(cube, x, y))
				*((unsigned int *)(offset + cube->mini_map.buffer)) = border;
			else if (ft_check_wall(cube, x, y))
				*((unsigned int *)(offset + cube->mini_map.buffer)) = wall;
			else
				*((unsigned int *)(offset + cube->mini_map.buffer)) = cube->map->floor;
			x++;
		}
		y++;
		x = 0;
	}
}

int create_minimap(t_cube *cube)
{
	cube->mini_map.img_ptr = mlx_new_image(cube->mlx, cube->win_x / 3, cube->win_y / 3);
	if (cube->mini_map.img_ptr == NULL)
	{
		mlx_destroy_window(cube->mlx, cube->win);
		mlx_destroy_display(cube->mlx);
		free(cube->mlx);
	}
	cube->mini_map.buffer = mlx_get_data_addr(cube->mini_map.img_ptr,
			&cube->mini_map.bpp, &cube->mini_map.line_len, &cube->mini_map.endian);
	cube->pos_mini_map.img_ptr = mlx_new_image(cube->mlx, cube->win_x / 3, cube->win_y / 3);
	if (cube->pos_mini_map.img_ptr == NULL)
	{
		mlx_destroy_window(cube->mlx, cube->win);
		mlx_destroy_display(cube->mlx);
		free(cube->mlx);
	}
	cube->pos_mini_map.buffer = mlx_get_data_addr(cube->pos_mini_map.img_ptr,
			&cube->pos_mini_map.bpp, &cube->pos_mini_map.line_len, &cube->pos_mini_map.endian);
	ft_set_minimap(cube);
	
	return (0);
	
}

void	put_position_minimap(t_cube *cube)
{
	int	x;
	int	y;
	int	offset;
	int	init_x;
	int finalx = (int) cube->posX;
	int finaly = (int) cube->posY;

	y = 0;
	init_x = (cube->win_x / 3) * 2;
	x = 0 + init_x;
	int	color = (255 << 16) | (0 << 8) | 0;
	while (y < cube->win_y / 3)	
	{
		while(x - init_x < cube->win_x / 3)
		{
			offset = (cube->mini_map.line_len * y) + (x * (cube->mini_map.bpp / 8));
			if (finaly == (cube->map->max_Y * y) / (cube->win_y / 3) && finalx == (cube->map->max_X * (x - init_x)) / (cube->win_x / 3))
				*((unsigned int *)(offset + cube->mini_map.buffer)) = color;
			x++;
		}
		y++;
		x = 0 + init_x;
	}

}

void	ft_reset_pos_minimap(t_cube *cube)
{
	int	x;
	int	y;
	int	offset;
	int	init_x;
	int finalx = (int) cube->posX;
	int finaly = (int) cube->posY;

	y = 0;
	init_x = (cube->win_x / 3) * 2;
	x = 0 + init_x;
	while (y < cube->win_y / 3)	
	{
		while(x - init_x < cube->win_x / 3)
		{
			offset = (cube->mini_map.line_len * y) + (x * (cube->mini_map.bpp / 8));
			if (finaly == (cube->map->max_Y * y) / (cube->win_y / 3) && finalx == (cube->map->max_X * (x - init_x)) / (cube->win_x / 3))
				*((unsigned int *)(offset + cube->mini_map.buffer)) = cube->map->floor;
			x++;
		}
		y++;
		x = 0 + init_x;
	}
}