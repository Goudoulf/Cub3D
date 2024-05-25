/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:54:23 by cassie            #+#    #+#             */
/*   Updated: 2024/05/24 16:42:29 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	((unsigned int *)(img->buffer))[x + y * 800] = color;
}

void	ft_set_floor_ceiling(t_cube *cube)
{
	int offset;
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y <cube->win_y)	
	{
		while(x < cube->win_x)
		{
			offset = (cube->img.line_len * y) + (x * (cube->img.bpp / 8));
			if (y < cube->win_y / 2)
				*((unsigned int *)(offset + cube->img.buffer)) = cube->map->ceiling;
			else
				*((unsigned int *)(offset + cube->img.buffer)) = cube->map->floor;
			x++;
		}
		y++;
		x = 0;
	}
}

int render(t_cube *cube)
{
	ft_set_floor_ceiling(cube);
	raycast(cube);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->img.img_ptr, 0, 0);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->mini_map.img_ptr, (cube->win_x / 3) * 2, 0);
	put_position_minimap(cube);
	return 0;
}
