/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:11:16 by dvo               #+#    #+#             */
/*   Updated: 2024/05/25 15:23:57 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int ft_border(t_cub *cub, int x, int y)
{
	if (x > (cub->win_x / 5) - 5 || x < 5)
		return (1);
	if (y > (cub->win_y / 5) - 5 || y < 5)
		return (1);
	return (0);
}

int ft_check_wall(t_cub *cub, int x, int y)
{
	int posx;
	int posy;

	posx = (cub->map->max_X * x) / (cub->win_x / 5);
	posy = (cub->map->max_Y * y) / (cub->win_y / 5);
	if (cub->map->final_map[posy][posx] == 1)
		return (1);
	return (0);
}

void	ft_set_minimap(t_cub *cub)
{
	int offset;
	int	x;
	int	y;

	x = 0;
	y = 0;

	int wall = (0 << 16) | (255 << 8) | 0;
	int border = (218 << 16) | (165 << 8) | 32;
	while (y < cub->win_y / 5)	
	{
		while(x < cub->win_x / 5)
		{
			offset = (cub->mini_map.img.line_len * y) + (x * (cub->mini_map.img.bpp / 8));
			if (ft_border(cub, x, y))
				*((unsigned int *)(offset + cub->mini_map.img.buffer)) = border;
			else if (ft_check_wall(cub, x, y))
				*((unsigned int *)(offset + cub->mini_map.img.buffer)) = wall;
			else
				*((unsigned int *)(offset + cub->mini_map.img.buffer)) = cub->map->floor;
			x++;
		}
		y++;
		x = 0;
	}
}

int create_minimap(t_cub *cub)
{
	cub->mini_map.img.img_ptr = mlx_new_image(cub->mlx, cub->win_x / 5, cub->win_y / 5);
	if (cub->mini_map.img.img_ptr == NULL)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	cub->mini_map.img.buffer = mlx_get_data_addr(cub->mini_map.img.img_ptr,
			&cub->mini_map.img.bpp, &cub->mini_map.img.line_len, &cub->mini_map.img.endian);
	cub->mini_map.img_pos.img_ptr = mlx_new_image(cub->mlx, cub->win_x / 5, cub->win_y / 5);
	if (cub->mini_map.img_pos.img_ptr == NULL)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	cub->mini_map.img_pos.buffer = mlx_get_data_addr(cub->mini_map.img.img_ptr,
			&cub->mini_map.img_pos.bpp, &cub->mini_map.img_pos.line_len, &cub->mini_map.img_pos.endian);
	ft_set_minimap(cub);
	
	return (0);
	
}

void	put_position_minimap(t_cub *cub)
{
	int	x;
	int	y;
	int	init_x;
	int finalx = (int) cub->ray.pos.x;
	int finaly = (int) cub->ray.pos.y;

	y = 0;
	init_x = (cub->win_x / 5);
	x = 0 + init_x;
	int	color = (255 << 16) | (0 << 8) | 0;
	while (y < cub->win_y / 5)	
	{
		while(x - init_x < cub->win_x / 5)
		{
			if (finaly == (cub->map->max_Y * y) / (cub->win_y / 5) &&
				finalx == (cub->map->max_X * (x - init_x)) / (cub->win_x / 5))
			{
				((unsigned int *)(cub->mini_map.img.buffer))[x + y * 1920 / 5] = color;
				((unsigned int *)(cub->mini_map.img.buffer))[cub->mini_map.last_pos.x 
					+ cub->mini_map.last_pos.y * 1920 / 5] = cub->map->floor;
				cub->mini_map.last_pos.x = x;
				cub->mini_map.last_pos.x = y;
			}
			x++;
		}
		y++;
		x = 0 + init_x;
	}
}
