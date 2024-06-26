/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:54:23 by cassie            #+#    #+#             */
/*   Updated: 2024/06/01 20:14:05 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
	ft_set_minimap(cub, (t_pos){0, 0}, (t_pos){(int) cub->ray->pos.x - 5,
		(int)cub->ray->pos.y - 5});
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img_ptr, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mini_map.img.img_ptr,
		(cub->win_x / 8) * 7, 0);
	return (0);
}
