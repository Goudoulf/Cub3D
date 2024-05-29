/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:54:23 by cassie            #+#    #+#             */
/*   Updated: 2024/05/29 15:25:47 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	((unsigned int *)(img->buffer))[x + y * 1920] = color;
}

void	ft_set_floor_ceiling(t_cub *cub)
{
	int	offset;
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < cub->win_y)
	{
		while (x < cub->win_x)
		{
			offset = (cub->img.line_len * y) + (x * (cub->img.bpp / 8));
			if (y < cub->win_y / 2)
				*((unsigned int *)(offset + cub->img.buffer))
					= cub->map->ceiling;
			else
				*((unsigned int *)(offset + cub->img.buffer)) = cub->map->floor;
			x++;
		}
		y++;
		x = 0;
	}
}

int	render(t_cub *cub)
{
	ft_bzero(cub->img.buffer, 1920 * 1080 * 4);
	ft_set_floor_ceiling(cub);
	raycast(cub);
	//ft_ennemy_move(cub);
	ft_set_minimap(cub);
	put_position_minimap(cub, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img_ptr, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mini_map.img.img_ptr,
		(cub->win_x / 5) * 4, 0);
	//if (cub->flag_die == 1)
	//	mlx_put_image_to_window(cub->mlx, cub->win,
//			cub->texture.scream.img_ptr, 0, 0);
	cub->view_ennemy = 0;
	return (0);
}
