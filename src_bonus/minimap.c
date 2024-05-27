/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:11:16 by dvo               #+#    #+#             */
/*   Updated: 2024/05/26 09:23:49 by cassie           ###   ########.fr       */
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

void	put_position_minimap(t_cub *cub, int color)
{
	int	x;
	int	y;
	int	init_x;
	float test_y;
	float test_x;
	y = 0;
	init_x = (cub->win_x / 5);
	x = init_x;
	if (!color)
		color = (255 << 16) | (0 << 8) | 0;
	while (y < cub->win_y / 5)	
	{
		while(x - init_x < cub->win_x / 5)
		{
			test_x = (cub->map->max_X * (x - init_x)) / (float)(cub->win_x / 5.0f);
			test_y = (cub->map->max_Y * y) / (float)(cub->win_y / 5.0f);
			if (cub->ray->pos.y + 0.3 > test_y && cub->ray->pos.y - 0.3 < test_y && \
			cub->ray->pos.x + 0.3 > test_x && cub->ray->pos.x - 0.3 < test_x)
				((unsigned int *)(cub->mini_map.img.buffer))[x + y * 1920 / 5] = color;
			x++;
		}
		y++;
		x = init_x;
	}
}
